cmake_minimum_required(VERSION 3.10)
project(cpp_echo_svc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 查找系统中的 Protobuf 库 (使用 CMake 原生的 FindProtobuf 模块)
find_package(Protobuf REQUIRED)
# 2. 包含头文件路径
include_directories(${Protobuf_INCLUDE_DIRS})
# 生成的 .pb.h 会放在 cmake 的 build 隐藏目录里，必须包含这个目录
include_directories(${CMAKE_CURRENT_BINARY_DIR})
# 3. 让 CMake 自动在当前环境下把 .proto 编译成 .pb.cc 和 .pb.h
# 它会自动生成 PROTO_SRCS 和 PROTO_HDRS 两个变量供下面使用
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/protocol/rpc_meta.proto)

# 生成可执行文件 rpc_test，包含 main.cpp 和 生成的 pb.cc
add_executable(rpc_test
        src/protocol/main.cpp
        ${PROTO_SRCS}
)

# 5. 链接 Protobuf 库
target_link_libraries(rpc_test ${Protobuf_LIBRARIES})

# 下面是你原本的其他测试文件，保持不变即可
add_executable(test_cpp src/test.cpp src/test.h)
add_executable(test_my_func src/algorithm.cpp src/algorithm.h)
