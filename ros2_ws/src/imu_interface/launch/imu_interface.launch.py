from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='imu_interface',
            executable='imu_interface_node',
            name='imu_interface_node',
            output='screen',
        ),
    ])