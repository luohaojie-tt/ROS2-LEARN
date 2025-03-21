#!/usr/bin/env python3
import rclpy
from std_msgs.msg import String

if __name__ == '__main__':
    rclpy.init()
    node = rclpy.create_node('yao_node_py')
    node.get_logger().info('PY 实现!')
    pub = node.create_publisher(String, 'yao_topic_py', 10)
    while rclpy.ok():
        node.get_logger().info('瑶妹妹有话讲：')
        msg = String()
        msg.data = '带带我'
        pub.publish(msg)
        node.get_logger().info('PY 发布消息: %s' % msg.data)
        rclpy.spin_once(node, timeout_sec=0.1)