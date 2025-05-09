cmake_minimum_required(VERSION 3.8)
project(map_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(nav_msgs REQUIRED)

add_executable(map_pub_node src/map_pub_node.cpp) 

ament_target_dependencies(map_pub_node rclcpp nav_msgs)


install(TARGETS
  map_pub_node
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/map_pub_nodepy.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_dependencies(rclpy nav_msgs)
ament_export_include_directories(include)
ament_export_libraries(map_pub_node map_pub_nodepy)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
