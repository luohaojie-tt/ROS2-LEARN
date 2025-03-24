#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>
/**
 * @brief 获取激光雷达扫描数据并打印前方距离信息。
 *
 * 该函数接收一个激光雷达的扫描消息，提取其中第180个角度的测距值（假设为正前方），
 * 并通过日志输出该距离值。
 *
 * @param msg 指向 sensor_msgs::msg::LaserScan 类型的共享指针，包含激光雷达的扫描数据。
 *            其中 ranges 数组存储了每个角度的测距值。
 * @return int 返回值固定为 0，表示函数执行成功。
 */

rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub;
int count = 0;
int getScanback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    // 打印激光雷达正前方的距离值（假设第180个角度为正前方）
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "前方距离: '%f' 米", msg->ranges[180]);
    float dis = msg->ranges[180];
    geometry_msgs::msg::Twist vel_cmd;
    if (count > 0)
    {
        count--;
        return 0;
    }

    if (dis < 1.5)
    {
        vel_cmd.angular.z = 0.5;
        count = 50;
    }
    else
    {
        vel_cmd.linear.x = 0.5;
    }
    vel_pub->publish(vel_cmd);
    return 0;
}

/**
 * @brief 主函数，初始化 ROS 2 节点并订阅激光雷达话题。
 *
 * 该函数完成以下任务：
 * 1. 初始化 ROS 2 系统；
 * 2. 创建一个名为 "lidar_node" 的节点；
 * 3. 订阅 "scan" 话题，接收激光雷达的扫描数据；
 * 4. 进入事件循环，持续处理回调函数。
 *
 * @param argc 命令行参数的数量。
 * @param argv 命令行参数的字符串数组。
 * @return int 返回值固定为 0，表示程序正常退出。
 */
int main(int argc, char *argv[])
{
    // 初始化 ROS 2 系统
    rclcpp::init(argc, argv);

    // 创建一个名为 "lidar_node" 的节点
    auto node = rclcpp::Node::make_shared("lidar_node");

    // 订阅 "scan" 话题，接收激光雷达数据，并绑定回调函数 getScanback
    auto sub = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, getScanback);

    vel_pub = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    // 进入事件循环，持续处理回调函数
    rclcpp::spin(node);

    return 0;
}
