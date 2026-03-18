FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# 安装 C++ 核心编译工具链、CMake 和 Protobuf
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    cmake \
    pkg-config \
    protobuf-compiler \
    libprotobuf-dev \
    && rm -rf /var/lib/apt/lists/*