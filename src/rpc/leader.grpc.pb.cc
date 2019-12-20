// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rpc/leader.proto

#include "rpc/leader.grpc.pb.h"
#include "rpc/leader.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace cluster {
    namespace rpc {

        static const char *ManagementService_method_names[] = {
            "/cluster.rpc.ManagementService/GetNetworkState",
            "/cluster.rpc.ManagementService/GreetAsCandidate",
            "/cluster.rpc.ManagementService/GreetAsLeader",
            "/cluster.rpc.ManagementService/PulseMonitor",
        };

        std::unique_ptr<ManagementService::Stub>
        ManagementService::NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
                                   const ::grpc::StubOptions &options) {
            (void)options;
            std::unique_ptr<ManagementService::Stub> stub(new ManagementService::Stub(channel));
            return stub;
        }

        ManagementService::Stub::Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel)
            : channel_(channel)
            , rpcmethod_GetNetworkState_(ManagementService_method_names[0],
                                         ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
            , rpcmethod_GreetAsCandidate_(ManagementService_method_names[1],
                                          ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
            , rpcmethod_GreetAsLeader_(ManagementService_method_names[2],
                                       ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
            , rpcmethod_PulseMonitor_(ManagementService_method_names[3],
                                      ::grpc::internal::RpcMethod::NORMAL_RPC, channel) {}

        ::grpc::Status
        ManagementService::Stub::GetNetworkState(::grpc::ClientContext *context,
                                                 const ::cluster::rpc::NetworkStateRequest &request,
                                                 ::cluster::rpc::NetworkStateResponse *response) {
            return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetNetworkState_,
                                                       context, request, response);
        }

        void ManagementService::Stub::experimental_async::GetNetworkState(
            ::grpc::ClientContext *context, const ::cluster::rpc::NetworkStateRequest *request,
            ::cluster::rpc::NetworkStateResponse *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GetNetworkState_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GetNetworkState(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::NetworkStateResponse *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GetNetworkState_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GetNetworkState(
            ::grpc::ClientContext *context, const ::cluster::rpc::NetworkStateRequest *request,
            ::cluster::rpc::NetworkStateResponse *response,
            ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GetNetworkState_, context, request,
                response, reactor);
        }

        void ManagementService::Stub::experimental_async::GetNetworkState(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::NetworkStateResponse *response,
            ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GetNetworkState_, context, request,
                response, reactor);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::NetworkStateResponse> *
        ManagementService::Stub::AsyncGetNetworkStateRaw(
            ::grpc::ClientContext *context, const ::cluster::rpc::NetworkStateRequest &request,
            ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::NetworkStateResponse>::Create(channel_.get(), cq,
                                                              rpcmethod_GetNetworkState_, context,
                                                              request, true);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::NetworkStateResponse> *
        ManagementService::Stub::PrepareAsyncGetNetworkStateRaw(
            ::grpc::ClientContext *context, const ::cluster::rpc::NetworkStateRequest &request,
            ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::NetworkStateResponse>::Create(channel_.get(), cq,
                                                              rpcmethod_GetNetworkState_, context,
                                                              request, false);
        }

        ::grpc::Status
        ManagementService::Stub::GreetAsCandidate(::grpc::ClientContext *context,
                                                  const ::cluster::rpc::Request &request,
                                                  ::cluster::rpc::Response *response) {
            return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GreetAsCandidate_,
                                                       context, request, response);
        }

        void ManagementService::Stub::experimental_async::GreetAsCandidate(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request *request,
            ::cluster::rpc::Response *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GreetAsCandidate_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GreetAsCandidate(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Response *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GreetAsCandidate_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GreetAsCandidate(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request *request,
            ::cluster::rpc::Response *response, ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GreetAsCandidate_, context, request,
                response, reactor);
        }

        void ManagementService::Stub::experimental_async::GreetAsCandidate(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Response *response, ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GreetAsCandidate_, context, request,
                response, reactor);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Response> *
        ManagementService::Stub::AsyncGreetAsCandidateRaw(::grpc::ClientContext *context,
                                                          const ::cluster::rpc::Request &request,
                                                          ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Response>::Create(channel_.get(), cq, rpcmethod_GreetAsCandidate_,
                                                  context, request, true);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Response> *
        ManagementService::Stub::PrepareAsyncGreetAsCandidateRaw(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request &request,
            ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Response>::Create(channel_.get(), cq, rpcmethod_GreetAsCandidate_,
                                                  context, request, false);
        }

        ::grpc::Status
        ManagementService::Stub::GreetAsLeader(::grpc::ClientContext *context,
                                               const ::cluster::rpc::Request &request,
                                               ::cluster::rpc::Response *response) {
            return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GreetAsLeader_,
                                                       context, request, response);
        }

        void ManagementService::Stub::experimental_async::GreetAsLeader(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request *request,
            ::cluster::rpc::Response *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GreetAsLeader_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GreetAsLeader(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Response *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_GreetAsLeader_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::GreetAsLeader(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request *request,
            ::cluster::rpc::Response *response, ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GreetAsLeader_, context, request, response,
                reactor);
        }

        void ManagementService::Stub::experimental_async::GreetAsLeader(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Response *response, ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_GreetAsLeader_, context, request, response,
                reactor);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Response> *
        ManagementService::Stub::AsyncGreetAsLeaderRaw(::grpc::ClientContext *context,
                                                       const ::cluster::rpc::Request &request,
                                                       ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Response>::Create(channel_.get(), cq, rpcmethod_GreetAsLeader_,
                                                  context, request, true);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Response> *
        ManagementService::Stub::PrepareAsyncGreetAsLeaderRaw(
            ::grpc::ClientContext *context, const ::cluster::rpc::Request &request,
            ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Response>::Create(channel_.get(), cq, rpcmethod_GreetAsLeader_,
                                                  context, request, false);
        }

        ::grpc::Status
        ManagementService::Stub::PulseMonitor(::grpc::ClientContext *context,
                                              const ::cluster::rpc::Heartbeat &request,
                                              ::cluster::rpc::Heartbeat *response) {
            return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_PulseMonitor_,
                                                       context, request, response);
        }

        void ManagementService::Stub::experimental_async::PulseMonitor(
            ::grpc::ClientContext *context, const ::cluster::rpc::Heartbeat *request,
            ::cluster::rpc::Heartbeat *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_PulseMonitor_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::PulseMonitor(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Heartbeat *response, std::function<void(::grpc::Status)> f) {
            ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(),
                                                     stub_->rpcmethod_PulseMonitor_, context,
                                                     request, response, std::move(f));
        }

        void ManagementService::Stub::experimental_async::PulseMonitor(
            ::grpc::ClientContext *context, const ::cluster::rpc::Heartbeat *request,
            ::cluster::rpc::Heartbeat *response,
            ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_PulseMonitor_, context, request, response,
                reactor);
        }

        void ManagementService::Stub::experimental_async::PulseMonitor(
            ::grpc::ClientContext *context, const ::grpc::ByteBuffer *request,
            ::cluster::rpc::Heartbeat *response,
            ::grpc::experimental::ClientUnaryReactor *reactor) {
            ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(
                stub_->channel_.get(), stub_->rpcmethod_PulseMonitor_, context, request, response,
                reactor);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Heartbeat> *
        ManagementService::Stub::AsyncPulseMonitorRaw(::grpc::ClientContext *context,
                                                      const ::cluster::rpc::Heartbeat &request,
                                                      ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Heartbeat>::Create(channel_.get(), cq, rpcmethod_PulseMonitor_,
                                                   context, request, true);
        }

        ::grpc::ClientAsyncResponseReader<::cluster::rpc::Heartbeat> *
        ManagementService::Stub::PrepareAsyncPulseMonitorRaw(
            ::grpc::ClientContext *context, const ::cluster::rpc::Heartbeat &request,
            ::grpc::CompletionQueue *cq) {
            return ::grpc_impl::internal::ClientAsyncResponseReaderFactory<
                ::cluster::rpc::Heartbeat>::Create(channel_.get(), cq, rpcmethod_PulseMonitor_,
                                                   context, request, false);
        }

        ManagementService::Service::Service() {
            AddMethod(new ::grpc::internal::RpcServiceMethod(
                ManagementService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC,
                new ::grpc::internal::RpcMethodHandler<ManagementService::Service,
                                                       ::cluster::rpc::NetworkStateRequest,
                                                       ::cluster::rpc::NetworkStateResponse>(
                    std::mem_fn(&ManagementService::Service::GetNetworkState), this)));
            AddMethod(new ::grpc::internal::RpcServiceMethod(
                ManagementService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC,
                new ::grpc::internal::RpcMethodHandler<
                    ManagementService::Service, ::cluster::rpc::Request, ::cluster::rpc::Response>(
                    std::mem_fn(&ManagementService::Service::GreetAsCandidate), this)));
            AddMethod(new ::grpc::internal::RpcServiceMethod(
                ManagementService_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC,
                new ::grpc::internal::RpcMethodHandler<
                    ManagementService::Service, ::cluster::rpc::Request, ::cluster::rpc::Response>(
                    std::mem_fn(&ManagementService::Service::GreetAsLeader), this)));
            AddMethod(new ::grpc::internal::RpcServiceMethod(
                ManagementService_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC,
                new ::grpc::internal::RpcMethodHandler<ManagementService::Service,
                                                       ::cluster::rpc::Heartbeat,
                                                       ::cluster::rpc::Heartbeat>(
                    std::mem_fn(&ManagementService::Service::PulseMonitor), this)));
        }

        ManagementService::Service::~Service() {}

        ::grpc::Status ManagementService::Service::GetNetworkState(
            ::grpc::ServerContext *context, const ::cluster::rpc::NetworkStateRequest *request,
            ::cluster::rpc::NetworkStateResponse *response) {
            (void)context;
            (void)request;
            (void)response;
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }

        ::grpc::Status
        ManagementService::Service::GreetAsCandidate(::grpc::ServerContext *context,
                                                     const ::cluster::rpc::Request *request,
                                                     ::cluster::rpc::Response *response) {
            (void)context;
            (void)request;
            (void)response;
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }

        ::grpc::Status
        ManagementService::Service::GreetAsLeader(::grpc::ServerContext *context,
                                                  const ::cluster::rpc::Request *request,
                                                  ::cluster::rpc::Response *response) {
            (void)context;
            (void)request;
            (void)response;
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }

        ::grpc::Status
        ManagementService::Service::PulseMonitor(::grpc::ServerContext *context,
                                                 const ::cluster::rpc::Heartbeat *request,
                                                 ::cluster::rpc::Heartbeat *response) {
            (void)context;
            (void)request;
            (void)response;
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }

    } // namespace rpc
} // namespace cluster
