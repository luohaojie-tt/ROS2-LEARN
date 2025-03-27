#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from tf_transformations import euler_from_quaternion
import math

def getImu_collback(msg):
    """
    回调函数，用于处理IMU传感器数据并计算欧拉角。

    参数:
        msg (sensor_msgs.msg.Imu): 包含IMU传感器数据的消息对象。
            - msg.orientation: IMU的方向信息，以四元数表示。
            - msg.orientation_covariance: 方向协方差矩阵，用于判断数据有效性。

    返回值:
        无返回值。该函数直接通过日志输出计算得到的欧拉角。
    """
    # 如果方向协方差的第一个元素小于0，说明数据无效，直接返回
    if msg.orientation_covariance[0] < 0:
        return

    # 提取四元数数据
    quationion = [
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w
    ]

    # 将四元数转换为欧拉角（roll, pitch, yaw）
    (roll, pitch, yaw) = euler_from_quaternion(quationion)

    # 将弧度制的角度转换为角度制
    roll = roll * 180 / math.pi
    pitch = pitch * 180 / math.pi
    yaw = yaw * 180 / math.pi

    # 输出欧拉角到日志中
    node.get_logger().info('roll: {}, pitch: {}, yaw: {}'.format(roll, pitch, yaw))


if __name__ == '__main__':
    # 初始化ROS2客户端库
    rclpy.init()

    # 创建一个节点，命名为'imu_node'
    node = Node('imu_node')

    # 订阅IMU数据话题，回调函数为getImu_collback，队列大小为10
    sub = node.create_subscription(Imu, 'imu/data', getImu_collback, 10)

    # 进入事件循环，等待消息并处理回调函数
    rclpy.spin(node)

    # 关闭ROS2客户端库
    rclpy.shutdown()