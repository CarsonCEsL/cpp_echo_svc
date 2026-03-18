// main.cpp
#include <iostream>
#include <string>
#include "rpc_message.h"
#include "rpc_meta.pb.h" // 引入 protobuf 生成的头文件

using namespace std;

int main() {
    // ---------------------------------------------------------
    // 阶段 1：模拟 Client 端封装请求
    // ---------------------------------------------------------
    cout << "=== 1. 客户端开始构造并序列化请求 ===" << endl;

    // 1.1 构造业务层面的 Protobuf 对象
    myrpc::RpcRequest req;
    req.set_service_name("UserService");
    req.set_method_name("Login");
    req.set_args("username=admin&password=123"); // 这里为了演示直接塞了字符串，实际也是个pb对象

    // 1.2 将 Protobuf 对象序列化为 string (即业务 Body)
    string serialized_body;
    if (!req.SerializeToString(&serialized_body)) {
        cerr << "Protobuf 序列化失败！" << endl;
        return -1;
    }
    cout << "Protobuf Body 序列化成功，长度: " << serialized_body.size() << " 字节" << endl;

    // 1.3 构造 RPC 协议对象
    RpcMessage client_msg;
    client_msg.header.request_id = 1001; // 设置一个全局唯一的请求 ID
    client_msg.header.body_size = serialized_body.size();
    client_msg.body = serialized_body;

    // 1.4 调用 encode 产生最终发往底层网卡的二进制流
    string network_stream = client_msg.encode();
    cout << "RPC 报文封包完成，最终网络字节流总长度: " << network_stream.size() << " 字节" << endl;
    cout << "(其中 Header: " << sizeof(RpcHeader) << " 字节, Body: " << serialized_body.size() << " 字节)\n" << endl;


    // ---------------------------------------------------------
    // 阶段 2：模拟网络传输 (这里假设 network_stream 通过 TCP 发送到了服务端)
    // ---------------------------------------------------------


    // ---------------------------------------------------------
    // 阶段 3：模拟 Server 端接收并解包
    // ---------------------------------------------------------
    cout << "=== 2. 服务端开始接收并反序列化请求 ===" << endl;

    // 3.1 收到二进制流，准备解析
    RpcMessage server_msg;
    bool success = server_msg.decode(network_stream.data(), network_stream.size());

    if (!success) {
        cerr << "RPC 报文解包失败，可能是半包或魔数错误！" << endl;
        return -1;
    }

    cout << "RPC 协议头解析成功！" << endl;
    cout << "- 校验魔数: 0x" << hex << server_msg.header.magic_num << dec << endl;
    cout << "- 请求 ID: " << server_msg.header.request_id << endl;
    cout << "- Body 长度: " << server_msg.header.body_size << endl;

    // 3.2 提取出 Body，反序列化回 Protobuf 对象
    myrpc::RpcRequest parsed_req;
    if (!parsed_req.ParseFromString(server_msg.body)) {
        cerr << "Protobuf 反序列化失败！" << endl;
        return -1;
    }

    // 3.3 执行本地路由分发 (Dispatcher 雏形)
    cout << "Protobuf Body 反序列化成功，业务数据还原如下：" << endl;
    cout << "- 目标服务: " << parsed_req.service_name() << endl;
    cout << "- 目标方法: " << parsed_req.method_name() << endl;
    cout << "- 方法参数: " << parsed_req.args() << endl;

    return 0;
}