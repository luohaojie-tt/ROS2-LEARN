#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

/**
 * @brief 主函数，用于发布速度命令
 *
 * 该节点初始化后，会创建一个名为"vel_node"的节点，并通过该节点创建一个/cmd_vel话题的发布者。
 * 发布的消息类型为geometry_msgs::msg::Twist，用于控制机器人的速度。
 * 消息内容设置为线性速度x分量为0.5，其他分量为0，表示机器人向前移动。
 * 循环以10Hz的频率发布速度命令，直到节点被关闭。
 *
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组
 * @return int 返回0表示正常退出
 */
int main(int argc, char *argv[])
{
    // 初始化rclcpp
    rclcpp::init(argc, argv);
    // 创建一个共享指针指向名为"vel_node"的节点
    auto node = rclcpp::Node::make_shared("vel_node");
    // 通过节点创建一个/cmd_vel话题的发布者，队列长度为10
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    // 创建一个Twist消息实例
    geometry_msgs::msg::Twist msg;
    // 设置线性速度x分量为0.5，表示机器人向前移动
    msg.linear.x = 0.5;
    // 设置线性速度y、z分量为0，表示没有在这些方向上的移动
    msg.linear.y = 0;
    msg.linear.z = 0;
    // 设置角速度x、y、z分量为0，表示没有旋转
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;
    // 创建一个Rate对象，用于控制循环频率，设置为10Hz
    rclcpp::Rate rate(10);
    // 当节点处于活动状态时，循环执行
    while (rclcpp::ok())
    {
        // 发布速度命令
        pub->publish(msg);
        // 按照Rate对象设置的频率休眠，以保持循环频率为10Hz
        rate.sleep();
    }

    return 0;
}
