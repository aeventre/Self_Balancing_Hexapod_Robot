from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="kinematics",
            executable="foward_kinematics_node",
            name="forward_kinematics_node",
            output="screen"
        ),
        Node(
            package="kinematics",
            executable="inverse_kinematics_node",
            name="inverse_kinematics_node",
            output="screen"
        ),
    ])