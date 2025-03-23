#!/usr/bin/env python3
import rclpy
from sensor_msgs.msg import LaserScan

def lidar_collback(msg):
    dist = msg.ranges[180]
    print("前方距离: %f",dist)

if __name__ == '__main__':
    rclpy.init()
    node = rclpy.create_node('lidar_node_py')
    sub = node.create_subscription(LaserScan, 'scan', lidar_collback, 10)
    rclpy.spin(node)