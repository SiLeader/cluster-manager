#include <iostream>
#include <random>

#include <cluster/detail/network.hpp>

#include "argparse/argparse.hpp"

int main(int argc, char **argv) {
    argparse::ArgumentParser parser("cms-test");
    parser.addArgument({"--port", "-p"}, "port number");
    parser.addArgument({"--dest", "-d"}, "destination port");

    auto args = parser.parseArgs(argc, argv);

    auto port = args.get<std::uint16_t>("port");

    cluster::Network nw("127.0.0.1", port);

    std::cout << "port: " << port << std::endl;

    auto dest = args.safeGet<int>("dest", 70000);
    if (dest <= 65000) {
        std::cout << "joining 127.0.0.1:" << dest << std::endl;
        nw.join({"127.0.0.1", static_cast<std::uint16_t>(dest)});
    }

    std::cout << "leader: " << nw.leader().host() << ":" << nw.leader().port() << std::endl;
}
