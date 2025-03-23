#!/usr/bin/env python3

# 导入rclpy模块，用于ROS 2的Python客户端库
import rclpy
# 导入Twist消息类型，用于发布机器人速度命令
from geometry_msgs.msg import Twist

# 主函数入口
if __name__ == '__main__':
    # 初始化rclpy库，必须在任何ROS操作之前调用
    rclpy.init()
    # 创建一个节点，命名为'vel_nodepy'
    node = rclpy.create_node('vel_nodepy')
    # 创建一个发布者，发布Twist类型的消息到'/cmd_vel'主题，队列长度为10
    pub = node.create_publisher(Twist, '/cmd_vel', 10)
    # 创建一个Twist消息实例，用于填充和发布速度命令
    twist = Twist()
    # 设置线性速度，这里仅设置x轴的线速度为0.5，其余线性和角速度分量为0
    twist.linear.x = 0.5
    twist.linear.y = 0.5
    twist.linear.z = 0.0
    twist.angular.x = 0.0
    twist.angular.y = 0.0
    twist.angular.z = 0.0
    
    # 进入主循环，当ROS节点处于活动状态时持续执行
    while rclpy.ok():
        # 发布速度命令
        pub.publish(twist)
        # 打印日志信息，记录当前发布的速度命令
        node.get_logger().info('PY 发布消息: %s' % twist)
        # 非阻塞地处理一次ROS事件，带有超时设置
        rclpy.spin_once(node, timeout_sec=0.1)