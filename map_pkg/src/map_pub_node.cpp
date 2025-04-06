#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("map_pub_node");

    // 创建发布器
    auto map_pub = node->create_publisher<nav_msgs::msg::OccupancyGrid>("/map", 10);

    // 设置发布频率
    rclcpp::Rate rate(1);

    while (rclcpp::ok())
    {
        // 创建 OccupancyGrid 消息
        nav_msgs::msg::OccupancyGrid map;

        // 填充 header
        map.header.frame_id = "map";
        map.header.stamp = node->now();

        // 填充 info
        map.info.origin.position.x = 0.0;
        map.info.origin.position.y = 0.0;
        map.info.resolution = 1.0;
        map.info.width = 4;
        map.info.height = 2;

        // 填充 data
        map.data.resize(map.info.width * map.info.height);
        map.data[0] = 100; // 障碍物
        map.data[1] = 100; // 障碍物
        map.data[2] = 0;   // 自由空间
        map.data[3] = -1;  // 未知区域

        // 发布消息
        map_pub->publish(map);

        // 添加日志输出
        RCLCPP_INFO(node->get_logger(), "Published OccupancyGrid message");

        // 按照 1 Hz 的频率休眠
        rate.sleep();
    }

    return 0;
}