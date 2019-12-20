//
// Created by cerussite on 2019/11/16.
//

#include <cluster/detail/network.hpp>

#include "pimpl/network.hpp"

namespace cluster {
    Network::Network(std::string_view host, std::uint16_t port)
        : _impl(std::make_shared<PImpl>(host, port)) {}

    bool Network::join(const Cluster &belonging) { return _impl->join(belonging); }

    [[nodiscard]] bool Network::isLeader(const Cluster &cluster) const {
        return leader() == cluster;
    }
    [[nodiscard]] Cluster Network::leader() const { return _impl->leader(); }
    [[nodiscard]] std::vector<Cluster> Network::belongingClusters() const {
        return _impl->belongingClusters();
    }
} // namespace cluster
