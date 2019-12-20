//
// Created by cerussite on 2019/11/16.
//

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "cluster.hpp"

namespace cluster {
    class Network final {
    private:
        class PImpl;

    private:
        std::shared_ptr<PImpl> _impl;

    public:
        Network(std::string_view host, std::uint16_t port);

        Network(const Network &) = default;
        Network(Network &&) = default;

        Network &operator=(const Network &) = default;
        Network &operator=(Network &&) = default;

        ~Network() = default;

    public:
        bool join(const Cluster &belonging);

        [[nodiscard]] bool isLeader(const Cluster &) const;
        [[nodiscard]] Cluster leader() const;
        [[nodiscard]] std::vector<Cluster> belongingClusters() const;
    };
} // namespace cluster
