#!/usr/bin/env python3
import rclpy
from nav_msgs.msg import OccupancyGrid
from rclpy.node import Node

# 主函数入口
if __name__ == '__main__':
    # 初始化ROS2客户端库
    rclpy.init()
    # 创建一个节点，命名为'map_pub_node'
    node = Node('map_pub_node')
    # 创建一个OccupancyGrid类型的发布者，发布地图信息到'/map'话题
    pub = node.create_publisher(OccupancyGrid, '/map', 10)
    
    # 初始化地图消息
    map_msg = OccupancyGrid()
    
    # 循环发布地图信息，直到节点被关闭
    while rclpy.ok():
        # 更新地图消息的时间戳
        map_msg.header.stamp = node.get_clock().now().to_msg()
        # 设置地图消息的参考坐标系
        map_msg.header.frame_id = 'map'
        # 设置地图的分辨率（每个像素代表的现实距离）
        map_msg.info.resolution = 1.0
        # 设置地图的宽度和高度（以像素为单位）
        map_msg.info.width = 4
        map_msg.info.height = 2
        
        # 设置地图原点的位置
        map_msg.info.origin.position.x = 1.0
        map_msg.info.origin.position.y = 1.0
        
        # 初始化地图数据，所有像素初始设为未知区域
        map_msg.data = [0] * (map_msg.info.width * map_msg.info.height)
        
        # 手动设置特定像素的值，100表示占用，-1表示未知，0表示空闲
        map_msg.data[0] = 100
        map_msg.data[1] = 100
        map_msg.data[2] = 0
        map_msg.data[3] = -1
        
        # 发布地图消息
        pub.publish(map_msg)
        # 在日志中记录地图消息的发布
        node.get_logger().info('发布地图消息')
        # 非阻塞地处理一次ROS2事件循环
        rclpy.spin_once(node, timeout_sec=0.1)