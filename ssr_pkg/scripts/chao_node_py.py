#!/usr/bin/env python3
import rclpy
from std_msgs.msg import String

if __name__ == '__main__':
    rclpy.init()
    node = rclpy.create_node('chao_node_py')
    node.get_logger().info('PY 实现!')
    pub = node.create_publisher(String, 'chao_topic_py', 10)
    while rclpy.ok():
        node.get_logger().info('马超有话讲：')
        msg = String()
        msg.data = '一起来开黑'
        pub.publish(msg)
        node.get_logger().info('PY 发布消息: %s' % msg.data)
        rclpy.spin_once(node, timeout_sec=0.1)