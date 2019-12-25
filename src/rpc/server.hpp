//
// Created by cerussite on 2019/11/16.
//

#pragma once

#include <random>
#include <thread>

#include <grpc++/grpc++.h>

#include <cluster/detail/cluster.hpp>

#include "leader.pb.h"

#include "leader.grpc.pb.h"

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

namespace cluster::rpc {
    namespace detail {
        struct ClusterIdHash {
            std::size_t operator()(const cluster::rpc::ClusterId &cluster) const {
                static std::hash<std::string> strHash;
                static std::hash<std::uint32_t> u32Hash;

                return strHash(cluster.host()) ^ u32Hash(cluster.port());
            }
        };

        inline int threeWayComparison(const Term &lhs, const Term &rhs) {
            if (unlikely(lhs.counter_size() != rhs.counter_size())) {
                return lhs.counter_size() - rhs.counter_size();
            }

            for (int i = 0; i < lhs.counter_size(); ++i) {
                if (lhs.counter(i) != rhs.counter(i)) {
                    return static_cast<int>(lhs.counter(i)) - static_cast<int>(rhs.counter(i));
                }
            }
            return 0;
        }
    } // namespace detail

    inline bool operator<(const Term &lhs, const Term &rhs) {
        return detail::threeWayComparison(lhs, rhs) < 0;
    }
    inline bool operator==(const Term &lhs, const Term &rhs) {
        return detail::threeWayComparison(lhs, rhs) == 0;
    }
    inline bool operator!=(const Term &lhs, const Term &rhs) { return !(lhs == rhs); }
    inline bool operator<=(const Term &lhs, const Term &rhs) { return lhs < rhs || lhs == rhs; }
    inline bool operator>(const Term &lhs, const Term &rhs) { return !(lhs <= rhs); }
    inline bool operator>=(const Term &lhs, const Term &rhs) { return !(lhs < rhs); }

    inline bool operator==(const ClusterId &lhs, const ClusterId &rhs) {
        return lhs.port() == rhs.port() && lhs.host() == rhs.host();
    }

    inline void Increment(cluster::rpc::Term &term) {
        for (std::size_t i = 0; i < term.counter_size(); ++i) {
            auto value = term.counter(i);
            if (value != std::numeric_limits<decltype(value)>::max()) {
                term.set_counter(i, ++value);
                return;
            }
            term.set_counter(i, 0);
        }
        term.add_counter(0);
    }

    class LeaderRpc : public ManagementService::Service {
    private:
        enum class Status {
            Follower,
            Candidate,
            Leader,
        };

    private:
        struct RpcClient {
            std::shared_ptr<grpc::Channel> channel;
            std::unique_ptr<cluster::rpc::ManagementService::Stub> stub;

            RpcClient() = default;
            explicit RpcClient(const ClusterId &cluster)
                : channel(grpc::CreateChannel(cluster.host() + ":" + std::to_string(cluster.port()),
                                              grpc::InsecureChannelCredentials()))
                , stub(cluster::rpc::ManagementService::NewStub(channel)) {}

            RpcClient(const RpcClient &) = delete;
            RpcClient(RpcClient &&) = default;

            RpcClient &operator=(const RpcClient &) = delete;
            RpcClient &operator=(RpcClient &&) = default;

            ~RpcClient() = default;
        };

    private:
        cluster::rpc::ClusterId _myself;

        std::unordered_map<cluster::rpc::ClusterId, std::shared_ptr<RpcClient>,
                           detail::ClusterIdHash>
            _belonging;

        cluster::rpc::ClusterId _currentLeader;
        cluster::rpc::Term _currentTerm;
        Status _currentStatus = Status::Follower;

        std::thread _serverThread, _heartbeatThread;
        std::atomic<bool> _isRunning;

    public:
        LeaderRpc(std::string_view host, std::uint16_t port)
            : _isRunning(true) {
            _myself.set_host(host.data(), host.size());
            _myself.set_port(port);

            _currentLeader = _myself;
            _currentTerm = Term();
            _currentTerm.add_counter(0);

            _belonging.emplace(_myself, nullptr);

            startHeartbeat();
        }

        ~LeaderRpc() {
            if (_serverThread.joinable()) {
                _serverThread.join();
            }
            _isRunning = false;
            if (_heartbeatThread.joinable()) {
                _heartbeatThread.join();
            }
        }

    private:
        void doElection() {
            static std::mt19937 mt(std::random_device{}());
            static std::uniform_int_distribution<> rand(1, 1000);

            std::this_thread::sleep_for(std::chrono::milliseconds(rand(mt)));
            _currentStatus = Status::Candidate;
            Increment(_currentTerm);

            for (const auto &cr : _belonging) {
                grpc::ClientContext ctx;
                Request req;
                *req.mutable_from() = _myself;
                *req.mutable_term() = _currentTerm;

                Response res;
                if (!cr.second) {
                    continue;
                }
                auto status = cr.second->stub->GreetAsCandidate(&ctx, req, &res);

                switch (status.error_code()) {
                case ::grpc::StatusCode::FAILED_PRECONDITION:
                case ::grpc::StatusCode::DEADLINE_EXCEEDED:
                    _currentStatus = Status::Follower;
                    joinToNetwork(cr.first);
                    goto end_election;

                case ::grpc::StatusCode::ALREADY_EXISTS:
                    doElection();
                    return;

                default:
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(rand(mt)));

            for (const auto &cr : _belonging) {
                grpc::ClientContext ctx;
                Request req;
                *req.mutable_from() = _myself;
                *req.mutable_term() = _currentTerm;

                Response res;
                if (!cr.second) {
                    continue;
                }
                auto status = cr.second->stub->GreetAsLeader(&ctx, req, &res);

                switch (status.error_code()) {
                case ::grpc::StatusCode::FAILED_PRECONDITION:
                case ::grpc::StatusCode::DEADLINE_EXCEEDED:
                    _currentStatus = Status::Follower;
                    joinToNetwork(cr.first);
                    goto end_election;

                default:
                    break;
                }
            }

            _currentStatus = Status::Leader;
            _currentLeader = _myself;

        end_election:
            return;
        }

    public:
        void runHeartbeat() {
            while (_isRunning) {
                Heartbeat hb;
                *hb.mutable_from() = _myself;
                *hb.mutable_term() = _currentTerm;

                for (const auto &cr : _belonging) {
                    auto rpc = cr.second;
                    if (!rpc) {
                        continue;
                    }
                    Heartbeat res;

                    grpc::ClientContext ctx;
                    if (likely(rpc->stub->PulseMonitor(&ctx, hb, &res).ok())) {
                        continue;
                    }

                    // bad response

                    if (unlikely(cr.first == _currentLeader)) {
                        doElection();
                    }
                }
                rehashNetwork(_currentLeader);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        void startHeartbeat() {
            _heartbeatThread = std::thread([this] { runHeartbeat(); });
        }

    public:
        void runServer() {
            grpc::ServerBuilder builder;
            builder.AddListeningPort(_myself.host() + ":" + std::to_string(_myself.port()),
                                     grpc::InsecureServerCredentials());
            builder.RegisterService(this);

            auto server = builder.BuildAndStart();
            server->Wait();
        }

        void startServer() {
            _serverThread = std::thread([this] { runServer(); });
        }

    public:
        const ClusterId &currentLeader() const { return _currentLeader; }

        std::vector<cluster::rpc::ClusterId> belongingClusters() const {
            std::vector<cluster::rpc::ClusterId> bc(std::size(_belonging));

            using Pair =
                typename std::unordered_map<cluster::rpc::ClusterId, std::shared_ptr<RpcClient>,
                                            detail::ClusterIdHash>::value_type;
            std::transform(std::begin(_belonging), std::end(_belonging), std::begin(bc),
                           [](const Pair &p) { return p.first; });
            return bc;
        }

    public:
        bool rehashNetwork(const ClusterId &belongingCluster) {
            if (_currentLeader == _myself) {
                std::vector<ClusterId> unavailableClusters;
                for (const auto &cr : _belonging) {
                    if (!(cr.second && joinToNetwork(cr.first))) {
                        unavailableClusters.emplace_back(cr.first);
                    }
                }
                for (const auto &uc : unavailableClusters) {
                    _belonging.erase(uc);
                }
                return true;
            }
            return joinToNetwork(belongingCluster);
        }

        bool joinToNetwork(const ClusterId &belongingCluster) {
            auto rc = std::make_shared<RpcClient>(belongingCluster);

            rpc::NetworkStateRequest req;
            req.set_allocated_from(&_myself);

            grpc::ClientContext ctx;
            rpc::NetworkStateResponse res;

            auto status = rc->stub->GetNetworkState(&ctx, req, &res);
            req.release_from();
            if (unlikely(!status.ok())) {
                return false;
            }

            for (const auto &cluster : res.clusters()) {
                if (unlikely(cluster == _myself)) {
                    continue;
                }
                _belonging.emplace(cluster, std::make_shared<RpcClient>(cluster));
            }
            _currentLeader = res.leader();
            _currentTerm = res.term();

            return true;
        }

    public:
        ::grpc::Status GetNetworkState(::grpc::ServerContext *context,
                                       const ::cluster::rpc::NetworkStateRequest *request,
                                       ::cluster::rpc::NetworkStateResponse *response) override {
            if (likely(_belonging.find(request->from()) == std::end(_belonging))) {
                _belonging.emplace(request->from(), std::make_shared<RpcClient>(request->from()));
            }

            *response->mutable_term() = _currentTerm;
            *response->mutable_from() = _myself;
            for (const auto &cluster : _belonging) {
                auto clusterArea = response->add_clusters();
                *clusterArea = cluster.first;
            }

            *response->mutable_leader() = _currentLeader;
            return ::grpc::Status::OK;
        }

        ::grpc::Status GreetAsCandidate(::grpc::ServerContext *context,
                                        const ::cluster::rpc::Request *request,
                                        ::cluster::rpc::Response *response) override {
            *response->mutable_from() = _myself;

            if (request->term() == _currentTerm) {
                *response->mutable_term() = _currentTerm;
                switch (_currentStatus) {
                case Status::Candidate:
                    return ::grpc::Status(::grpc::StatusCode::ALREADY_EXISTS,
                                          "I am Candidate on specified term.");
                case Status::Leader:
                    return ::grpc::Status(::grpc::StatusCode::FAILED_PRECONDITION,
                                          "I am Leader on specified term.");
                default:
                    // OK
                    break;
                }
            } else if (request->term() > _currentTerm) {
                _currentTerm = request->term();
                _currentStatus = Status::Follower;
                *response->mutable_term() = _currentTerm;

            } else { // request->term() < _currentTerm
                *response->mutable_term() = _currentTerm;
                return ::grpc::Status(::grpc::StatusCode::DEADLINE_EXCEEDED, "term is ended.");
            }

            return ::grpc::Status::OK;
        }

        ::grpc::Status GreetAsLeader(::grpc::ServerContext *context,
                                     const ::cluster::rpc::Request *request,
                                     ::cluster::rpc::Response *response) override {
            *response->mutable_from() = _myself;

            if (unlikely(request->term() == _currentTerm && _currentStatus == Status::Leader)) {
                *response->mutable_term() = _currentTerm;
                return ::grpc::Status(::grpc::StatusCode::FAILED_PRECONDITION,
                                      "I am Leader on specified term.");
            }
            if (request->term() < _currentTerm) {
                *response->mutable_term() = _currentTerm;
                return ::grpc::Status(::grpc::StatusCode::DEADLINE_EXCEEDED, "term is ended.");
            }

            _currentTerm = request->term();
            _currentStatus = Status::Follower;

            *response->mutable_term() = _currentTerm;
            return ::grpc::Status::OK;
        }

        ::grpc::Status PulseMonitor(::grpc::ServerContext *context,
                                    const ::cluster::rpc::Heartbeat *request,
                                    ::cluster::rpc::Heartbeat *response) override {
            Heartbeat hb;
            *response->mutable_from() = _myself;
            *response->mutable_term() = _currentTerm;
            return ::grpc::Status::OK;
        }
    };
} // namespace cluster::rpc
