cmake_minimum_required(VERSION 3.28.3)
project(cpp_echo_svc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_echo_svc
        src/protocol/rpc_message.h
        src/protocol/main.cpp)

add_executable(test_cpp src/test.cpp
                src/test.h)

add_executable(test_my_func src/algorithm.cpp
                src/algorithm.h)

target_compile_options(cpp_echo_svc PRIVATE -Wall -Wextra -O2 -g)
target_link_libraries(cpp_echo_svc PRIVATE pthread)
