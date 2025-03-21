from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ssr_pkg',
            executable='chao_node_py.py',
            name='chao_node_py'
        ),
        Node(
            package='ssr_pkg',
            executable='yao_node_py.py',
            name='yao_node_py'
        ),
        Node(
            package='atr_pkg',
            executable='ma_node_py.py',
            name='ma_node_py',
            prefix='xterm -e'
        ),
    ])