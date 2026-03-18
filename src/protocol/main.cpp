#include <iostream>
#include <string>
#include "rpc_message.h"
#include "rpc_meta.pb.h"

using namespace std;

int main() {
    // ---------------------------------------------------------
    // 阶段 1：模拟 Client 端疯狂连发两个请求 (产生粘包)
    // ---------------------------------------------------------
    cout << "=== 1. 客户端连续构造并序列化两个请求 ===" << endl;

    // 构造请求 A
    myrpc::RpcRequest req1;
    req1.set_service_name("UserService");
    req1.set_method_name("Login");
    req1.set_args("username=admin");
    string body1; req1.SerializeToString(&body1);

    RpcMessage msg1;
    msg1.header.request_id = 1001;
    msg1.header.body_size = body1.size();
    msg1.body = body1;

    // 构造请求 B
    myrpc::RpcRequest req2;
    req2.set_service_name("OrderService");
    req2.set_method_name("GetOrder");
    req2.set_args("order_id=999");
    string body2; req2.SerializeToString(&body2);

    RpcMessage msg2;
    msg2.header.request_id = 1002;
    msg2.header.body_size = body2.size();
    msg2.body = body2;

    // 【核心模拟】：TCP 底层把两个包粘在了一起
    string sticky_stream = msg1.encode() + msg2.encode();

    cout << "TCP 粘包流构造完成，总长度: " << sticky_stream.size() << " 字节\n" << endl;


    // ---------------------------------------------------------
    // 阶段 2：模拟 Server 端从缓冲区循环解包
    // ---------------------------------------------------------
    cout << "=== 2. 服务端开始处理粘包流 ===" << endl;

    // 模拟底层网络接收缓冲区
    const char* buffer_ptr = sticky_stream.data();
    size_t remaining_len = sticky_stream.size();
    int packet_count = 0;

    // 只要缓冲区里还有数据，就尝试解包
    while (remaining_len > 0) {
        RpcMessage server_msg;

        // 尝试从当前指针位置解析一个包
        bool success = server_msg.decode(buffer_ptr, remaining_len);

        if (!success) {
            cout << "剩余数据不足一个完整的包（半包），等待下一次网络接收..." << endl;
            break; // 跳出循环，等底层 epoll 再次触发可读事件
        }

        packet_count++;
        cout << "\n[成功拆出第 " << packet_count << " 个包]" << endl;
        cout << "- 请求 ID: " << server_msg.header.request_id << endl;

        myrpc::RpcRequest parsed_req;
        parsed_req.ParseFromString(server_msg.body);
        cout << "- 调用目标: " << parsed_req.service_name() << "::" << parsed_req.method_name() << endl;

        // 【最关键的一步】：计算当前包消耗的字节，滑动指针
        size_t consumed_bytes = sizeof(RpcHeader) + server_msg.header.body_size;
        buffer_ptr += consumed_bytes;      // 指针向后移动
        remaining_len -= consumed_bytes;   // 剩余长度减少

        cout << "  (消耗了 " << consumed_bytes << " 字节，缓冲区剩余 " << remaining_len << " 字节)" << endl;
    }

    cout << "\n=== 粘包处理完毕，共解析出 " << packet_count << " 个完整请求 ===" << endl;

    return 0;
}