//
// Created by cerussite on 2019/11/16.
//

#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace cluster {
    class Cluster final {
    private:
        std::string _host;
        std::uint16_t _port;

    public:
        Cluster(std::string_view host, std::uint16_t port)
            : _host(host)
            , _port(port) {}

        Cluster()
            : _host()
            , _port() {}

        Cluster(const Cluster &) = default;
        Cluster(Cluster &&) = default;

        Cluster &operator=(const Cluster &) = default;
        Cluster &operator=(Cluster &&) = default;

        ~Cluster() = default;

    public:
        [[nodiscard]] const std::string &host() const { return _host; }
        [[nodiscard]] std::uint16_t port() const noexcept { return _port; }

    public:
        bool operator==(const Cluster &rhs) const {
            return port() == rhs.port() && host() == rhs.host();
        }
        bool operator!=(const Cluster &rhs) const { return !((*this) == rhs); }
    };
} // namespace cluster
