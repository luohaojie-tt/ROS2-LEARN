#!/usr/bin/env python3
import rclpy
from std_msgs.msg import String

def chao_collback(msg):
    print('PY 收到消息: %s' % msg.data)

def yao_collback(msg):
    print('PY 收到消息: %s' % msg.data)

if __name__ == '__main__':
    rclpy.init()
    node = rclpy.create_node('chao_node_py')
    sub = node.create_subscription(String, 'chao_topic_py', chao_collback, 10)
    sub2 = node.create_subscription(String, 'yao_topic_py', yao_collback, 10)
    

    rclpy.spin(node)

    rclpy.shutdown()