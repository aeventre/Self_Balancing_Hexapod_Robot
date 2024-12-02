import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
import numpy as np

class kinematics(Node):
    def __init__(self):
        super().__init__('forward_kinematics_node')

        # Hexapod dimensions (adjust these values to match your robot)
        self.coxa_length = 0.044  # meters
        self.femur_length = 0.08  # meters
        self.tibia_length = 0.155  # meters

        # Subscribers and publishers
        self.joint_angles_sub = self.create_subscription(
            Float32MultiArray,
            'joint_angles',
            self.joint_angles_callback,
            10
        )
        self.foot_positions_pub = self.create_publisher(
            Float32MultiArray,
            'foot_positions',
            10
        )

        self.get_logger().info('Forward Kinematics Node initialized.')

    def joint_angles_callback(self, msg):
        self.get_logger().info('Received joint_angles.')

        # Validate and parse the input
        joint_angles = np.array(msg.data)
        if len(joint_angles) != 18:
            self.get_logger().error('Invalid number of joint angles. Expected 18 values.')
            return

        joint_angles = joint_angles.reshape(6, 3)  # 6 legs, 3 joints each
        foot_positions = []

        # Compute forward kinematics for each leg
        for i, angles in enumerate(joint_angles):
            foot_position = self.compute_foot_position(i, angles)
            foot_positions.extend(foot_position)

        # Publish foot positions
        foot_positions_msg = Float32MultiArray()
        foot_positions_msg.data = foot_positions
        self.foot_positions_pub.publish(foot_positions_msg)
        self.get_logger().info('Published foot_positions.')

    def compute_foot_position(self, leg_index, joint_angles):
        """
        Compute the foot position for a given leg based on its joint angles.

        Parameters:
        - leg_index: Index of the leg (0 to 5)
        - joint_angles: Joint angles [coxa, femur, tibia] in radians

        Returns:
        - 3D position of the foot as [x, y, z]
        """
        coxa_angle, femur_angle, tibia_angle = joint_angles

        # Transformations
        # 1. Coxa
        x_coxa = self.coxa_length * np.cos(coxa_angle)
        y_coxa = self.coxa_length * np.sin(coxa_angle)

        # 2. Femur
        femur_total_angle = femur_angle
        x_femur = x_coxa + self.femur_length * np.cos(femur_total_angle)
        z_femur = -self.femur_length * np.sin(femur_total_angle)

        # 3. Tibia
        tibia_total_angle = femur_total_angle + tibia_angle
        x_tibia = x_femur + self.tibia_length * np.cos(tibia_total_angle)
        z_tibia = z_femur - self.tibia_length * np.sin(tibia_total_angle)

        # Foot position
        foot_position = [x_tibia, y_coxa, z_tibia]
        self.get_logger().info(
            f'Leg[{leg_index}] Angles: {joint_angles} -> Foot Position: {foot_position}'
        )
        return foot_position


def main(args=None):
    rclpy.init(args=args)
    node = ForwardKinematicsNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()