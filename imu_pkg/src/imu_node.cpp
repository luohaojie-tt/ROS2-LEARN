#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/msg/twist.hpp"

rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub;

/**
 * @brief 回调函数，用于处理IMU数据并计算横滚角、俯仰角和偏航角。
 *
 * 该函数在接收到新的IMU消息时被调用。它通过检查方向协方差来判断方向数据是否有效。
 * 如果数据有效，则将四元数方向转换为欧拉角（横滚角、俯仰角、偏航角），并将结果记录到日志中。
 * 最后根据偏航角与目标角度的差异生成速度指令并发布。
 *
 * @param msg 指向传入IMU消息的共享指针，包含方向和其他数据。
 *            - msg->orientation: 表示IMU方向的四元数。
 *            - msg->orientation_covariance: 方向协方差矩阵，第一个元素为负值时表示数据无效。
 */
void getImubCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
    // 如果方向协方差的第一个元素小于0，表示方向数据无效，直接返回
    if (msg->orientation_covariance[0] < 0)
    {
        return;
    }

    double roll, pitch, yaw;

    // 将四元数方向转换为tf2四元数
    tf2::Quaternion quat(msg->orientation.x, msg->orientation.y, msg->orientation.z, msg->orientation.w);

    // 将四元数转换为旋转矩阵，并提取横滚角、俯仰角和偏航角
    tf2::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    // 将弧度转换为角度以便于阅读
    roll = roll * 180 / M_PI;
    pitch = pitch * 180 / M_PI;
    yaw = yaw * 180 / M_PI;

    // 记录计算得到的横滚角、俯仰角和偏航角
    RCLCPP_INFO(rclcpp::get_logger("imu_node"), "横滚角: %f, 俯仰角: %f, 偏航角: %f", roll, pitch, yaw);

    // 计算偏航角与目标角度的差异，并生成角速度指令
    double target_yaw = 0;
    double diff_angle = target_yaw - yaw;
    geometry_msgs::msg::Twist vel_cmd;
    vel_cmd.angular.z = diff_angle * 0.01;

    // 发布角速度指令
    vel_pub->publish(vel_cmd);
}

/**
 * @brief 主函数，用于初始化ROS 2节点并订阅IMU数据。
 *
 * 该函数初始化ROS 2环境，创建一个名为"imu_node"的节点，并订阅"/imu/data"主题以接收IMU消息。
 * 同时创建一个发布者用于发布速度指令。然后进入ROS 2事件循环以处理传入的消息。
 *
 * @param argc 命令行参数的数量。
 * @param argv 命令行参数的数组。
 * @return int 返回退出代码，通常0表示成功。
 */
int main(int argc, char *argv[])
{
    // 初始化ROS 2环境
    rclcpp::init(argc, argv);

    // 创建指向ROS 2节点的共享指针
    auto node = rclcpp::Node::make_shared("imu_node");

    // 订阅"/imu/data"主题，并指定回调函数处理IMU消息
    auto imu_sub = node->create_subscription<sensor_msgs::msg::Imu>("/imu/data", 10, getImubCallback);

    // 创建发布者，用于发布速度指令
    vel_pub = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    // 进入ROS 2事件循环以处理回调函数
    rclcpp::spin(node);

    // 关闭ROS 2环境
    rclcpp::shutdown();

    return 0;
}