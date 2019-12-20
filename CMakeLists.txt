cmake_minimum_required(VERSION 3.15)
project(ClusterManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)
include_directories($ENV{GRPC_ROOT}/include $ENV{PROTOBUF_ROOT}/include)

set(CMS_PRIVATE_LIBDIR $ENV{PROTOBUF_ROOT}/lib $ENV{GRPC_ROOT}/lib)

add_library(cluster
        include/cluster/detail/cluster.hpp
        include/cluster/detail/network.hpp
        src/pimpl/network.hpp
        src/rpc/leader.grpc.pb.cc
        src/rpc/leader.grpc.pb.h
        src/rpc/leader.pb.cc
        src/rpc/leader.pb.h
        src/rpc/server.hpp
        src/network.cpp)
target_link_directories(cluster PUBLIC ${CMS_PRIVATE_LIBDIR})
target_link_libraries(cluster protobuf grpc gpr grpc++ pthread)

add_executable(test
        main.cpp)
target_link_libraries(test cluster)