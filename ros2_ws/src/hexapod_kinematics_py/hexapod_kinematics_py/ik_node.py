import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
import numpy as np  # Ensure numpy is imported

class InverseKinematicsNode(Node):
    def __init__(self):
        super().__init__('inverse_kinematics_node')
        self.create_subscription(
            Float32MultiArray,
            'leg_commands',
            self.leg_commands_callback,
            10
        )
        self.publisher_ = self.create_publisher(
            Float32MultiArray,
            'joint_angles',
            10
        )
        self.get_logger().info('Inverse Kinematics Node initialized.')

    def leg_commands_callback(self, msg):
        self.get_logger().info('Received leg_commands.')
        targets = np.array(msg.data).reshape(-1, 3)  # Reshape into N x 3 array
        self.get_logger().info(f'Targets: {targets}')
        # Perform IK computation (dummy output for now)
        joint_angles = Float32MultiArray()
        joint_angles.data = [0.0] * 18  # Replace with actual IK results
        self.publisher_.publish(joint_angles)
        self.get_logger().info('Published joint angles.')

def main(args=None):
    rclpy.init(args=args)
    node = InverseKinematicsNode()
    rclpy.spin(node)
    node.destroy_node()
    rcl
