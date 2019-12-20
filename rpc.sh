protoc --grpc_out src --cpp_out src --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` rpc/leader.proto
