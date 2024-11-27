from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='servo_control',
            executable='servo_control_node',
            name='servo_control_node',
            parameters=[
                {'enable_second_pca': False}  # Set to True to enable the second PCA
            ]
        )
    ])
