//
// Created by Carson on 2026/3/19.
//
#ifndef CPP_ECHO_SVC_RPC_MESSAGE_H
#define CPP_ECHO_SVC_RPC_MESSAGE_H

#pragma once
#include <cstdint>
#include <string>
#include <arpa/inet.h>

// 强制1字节对齐，防止编译器自动插入padding导致跨平台跨语言解析错误
#pragma pack(push, 1)

// 定义消息类型
enum class MsgType : uint8_t {
    REQUEST = 1,
    RESPONSE = 2,
    HEARTBEAT = 3
};

// 定义序列化方式
enum class SerializeType : uint8_t {
    PROTOBUF = 1,
    JSON = 2
};

// RPC 协议头结构体 (固定 16 字节)
struct RpcHeader {
    uint16_t magic_num;      // 魔数 (例如 0x1234)，用于快速校验这不是乱码数据
    uint8_t  version;        // 协议版本号 (例如 1)
    uint8_t  msg_type;       // 消息类型 (MsgType)
    uint8_t  serialize_type; // 序列化类型 (SerializeType)
    uint8_t  padding[3];     // 保留字段，凑齐字节数，也可用于未来扩展
    uint32_t body_size;      // 消息体长度 (用于解决粘包问题)
    uint32_t request_id;     // 请求 ID (用于支持全双工的异步调用，将请求和响应匹配)
};

#pragma pack(pop)

class RpcMessage {
public:
    RpcHeader header;
    std::string body; // 这里存放序列化后的二进制数据，如protobuf转化后的string

    RpcMessage() {
        header.magic_num = 0x1234;
        header.version = 1;
        header.msg_type = static_cast<uint8_t>(MsgType::REQUEST);
        header.serialize_type = static_cast<uint8_t>(SerializeType::PROTOBUF);

        std::memset(header.padding, 0, sizeof(header.padding));

        header.body_size = 0;
        header.request_id = 0;
    }

    // 序列化：将完整的RpcMessage转换为可以通过网络发送的字节流
    std::string encode() const {
        std::string buffer;
        // 这里需要将 header 里的多字节整型转换为网络字节序(大端序)，如 htonl, htons
        // 将 多字节的 整形转换为网络字节序，大端序
        RpcHeader net_header = header;
        net_header.magic_num = htons(header.magic_num);
        net_header.body_size = htonl(header.body_size);
        net_header.request_id = htonl(header.request_id);

        buffer.append(reinterpret_cast<const char*>(&net_header), sizeof(RpcHeader));
        buffer.append(body);
        return buffer;
    }

    // 反序列化：从字节流中解析出RpcMessage
    // 这里假设传入的buffer已经包含了一个完整的Header
    bool decode(const char* buffer, size_t len) {
        if (len < sizeof(RpcHeader)) {
            std::cerr << "[Debug] 数据包的长度小于协议头大小" << std::endl;
            return false;
        }

        // 拷贝Header
        // header = *reinterpret_cast<const RpcHeader*>(buffer);
        std::memcpy(&header, buffer, sizeof(RpcHeader));
        // 此处应将网络字节序转换成主机字节序，ntohl, ntohs
        header.magic_num = ntohs(header.magic_num);
        header.body_size = ntohl(header.body_size);
        header.request_id = ntohl(header.request_id);

        // 校验魔数
        if (header.magic_num != 0x1234) {
            std::cerr << "[Debug] 魔数校验失败，实际0x"
                << std::hex << header.magic_num << std::dec << std::endl;
            return false;
        }

        // 拷贝body
        if (len >= sizeof(RpcHeader) + header.body_size) {
            // buffer是其实，这段代码是跳过header长度，区body_size长度放进body，刚好是一个完整的RPC载荷
            body.assign(buffer + sizeof(RpcHeader), header.body_size);
            return true;
        }
        std::cerr << "[Debug] 半包校验失败! 当前收到的流总长度 len: " << len
                      << ", 协议头大小: " << sizeof(RpcHeader)
                      << ", Header中解析出的 body_size: " << header.body_size << std::endl;
        return false;
    }
};

#endif //CPP_ECHO_SVC_RPC_MESSAGE_H