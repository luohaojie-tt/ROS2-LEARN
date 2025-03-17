#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// 主函数，入口参数为命令行参数数量和参数本身
int main(int argc, char **argv)
{
    // 初始化rclcpp，必须作为使用rclcpp前的第一个调用
    rclcpp::init(argc, argv);

    // 打印"Hello World!"到控制台
    printf("Hello World!\n");
    priintf("你好!\n");

    // 创建一个名为"chao_node"的节点
    auto node = rclcpp::Node::make_shared("chao_node");

    // 在当前节点上创建一个发布者，发布字符串消息到"chao_topic"主题，队列长度为10
    auto publisher = node->create_publisher<std_msgs::msg::String>("chao_topic", 10);

    // 当rclcpp状态为ok时，循环执行以下操作
    while (rclcpp::ok())
    {
        // 创建一个字符串消息实例
        auto msg = std_msgs::msg::String();

        // 设置消息的数据内容为"Hello World!"
        msg.data = "Hello World!";

        // 发布消息
        publisher->publish(msg);

        // 处理节点中的一些工作，以保持节点响应
        rclcpp::spin_some(node);

        // 暂停1秒
        rclcpp::sleep_for(std::chrono::milliseconds(1000));
    }

    // 返回0表示程序正常结束
    return 0;
}