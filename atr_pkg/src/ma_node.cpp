#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

// 提取回调函数为独立函数，提高可读性和可维护性
void message_callback(const std_msgs::msg::String::SharedPtr msg)
{
    // 检查消息是否为空
    if (!msg)
    {
        RCLCPP_ERROR(rclcpp::get_logger("listener_node"), "Received null message");
        return;
    }

    // 使用更安全的日志格式化方式，避免潜在的格式化漏洞
    RCLCPP_INFO(rclcpp::get_logger("listener_node"), "I heard: [%s]", msg->data.c_str());
}

void yao_message_callback(const std_msgs::msg::String::SharedPtr msg)
{
    // 检查消息是否为空
    if (!msg)
    {
        RCLCPP_ERROR(rclcpp::get_logger("listener_node"), "Received null message");
        return;
    }

    // 使用更安全的日志格式化方式，避免潜在的格式化漏洞
    RCLCPP_INFO(rclcpp::get_logger("listener_node"), "I heard: [%s]", msg->data.c_str());
}
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("ma_node");
    auto sub = node->create_subscription<std_msgs::msg::String>("chao_topic", 10, message_callback);
    auto sub2 = node->create_subscription<std_msgs::msg::String>("yao_topic", 10, message_callback);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
    }

    return 0;
}
