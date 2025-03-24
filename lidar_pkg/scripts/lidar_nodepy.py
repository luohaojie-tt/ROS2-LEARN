#!/usr/bin/env python3
import rclpy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist


count = 0
vel_pub = None
def lidar_collback(msg):
    global vel_pub,count

    dist = msg.ranges[180]
    print("前方距离: %f",dist)
    vel_cmd = Twist()
    if count >0:
        count = count - 1
        return
    if dist < 1.5:
        vel_cmd.angular.z = 0.5
        count = 50
    else:
        vel_cmd.linear.x = 0.5
    vel_pub.publish(vel_cmd)

if __name__ == '__main__':
    rclpy.init()
    node = rclpy.create_node('lidar_node_py')
    sub = node.create_subscription(LaserScan, 'scan', lidar_collback, 10)
    vel_pub = node.create_publisher(Twist, '/cmd_vel', 10)
    rclpy.spin(node)