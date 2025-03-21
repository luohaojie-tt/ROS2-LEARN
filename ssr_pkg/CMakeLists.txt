cmake_minimum_required(VERSION 3.16)
project(ssr_pkg VERSION 0.1.0 LANGUAGES CXX)
 
# Compiler Configuration 
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Dependencies 
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
 
# Node Configuration 
add_executable(chao_node src/chao_node.cpp) 
target_include_directories(chao_node PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(chao_node PUBLIC rclcpp std_msgs)

add_executable(yao_node src/yao_node.cpp) 
target_include_directories(yao_node PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(yao_node PUBLIC rclcpp std_msgs)
 
# Installation 
install(TARGETS chao_node 
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS yao_node 
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/chao_node_py.py
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/yao_node_py.py
  DESTINATION lib/${PROJECT_NAME}
)
 
# Export dependencies 
ament_export_dependencies(rclcpp std_msgs)
ament_export_include_directories(include)
ament_export_libraries(chao_node yao_node)
 
# Testing 
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()
 
ament_package()