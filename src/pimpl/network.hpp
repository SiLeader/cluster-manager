//
// Created by cerussite on 2019/11/16.
//

#include <cluster/detail/network.hpp>

#include "../rpc/server.hpp"

namespace cluster {
    class Network::PImpl {
    private:
        rpc::LeaderRpc _rpc;

    public:
        PImpl(std::string_view host, std::uint16_t port)
            : _rpc(host, port) {
            _rpc.startServer();
        }

    public:
        bool join(const Cluster &belonging) {
            rpc::ClusterId cid;
            cid.set_host(belonging.host());
            cid.set_port(belonging.port());

            return _rpc.joinToNetwork(cid);
        }

        [[nodiscard]] Cluster leader() const {
            const auto &cid = _rpc.currentLeader();
            return Cluster(cid.host(), cid.port());
        }

        [[nodiscard]] std::vector<Cluster> belongingClusters() const {
            auto bc = _rpc.belongingClusters();
            std::vector<Cluster> cs(std::size(bc));

            std::transform(
                std::begin(bc), std::end(bc), std::begin(cs),
                [](const rpc::ClusterId &cid) { return Cluster(cid.host(), cid.port()); });

            return cs;
        }
    };
} // namespace cluster
