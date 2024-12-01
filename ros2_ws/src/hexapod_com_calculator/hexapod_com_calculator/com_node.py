import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point, PoseStamped
from std_msgs.msg import Bool
import numpy as np
from scipy.spatial.transform import Rotation as R


class CoMCalculatorNode(Node):
    def __init__(self):
        super().__init__('com_calculator_node')

        # Robot parameters
        self.num_legs = 6
        self.leg_positions = np.zeros((self.num_legs, 3))  # Leg positions in body frame
        self.foot_contacts = [False] * self.num_legs       # Foot switch states
        self.body_com = np.array([0.0, 0.0, 0.0])          # CoM assumed at the body center
        self.imu_offset = np.array([-0.012, 0.0, 0.03])    # IMU offset in meters

        # Subscribers
        self.leg_positions_sub = self.create_subscription(
            Point,
            'leg_positions',
            self.leg_positions_callback,
            10
        )

        self.imu_sub = self.create_subscription(
            PoseStamped,
            'imu/data',
            self.imu_callback,
            10
        )

        self.foot_switch_subs = [
            self.create_subscription(
                Bool,
                f'leg_{i}/foot_switch',
                lambda msg, leg_idx=i: self.foot_switch_callback(msg, leg_idx),
                10
            )
            for i in range(self.num_legs)
        ]

        # Timer for periodic CoM calculation
        self.timer = self.create_timer(0.1, self.calculate_com)

        # Internal data
        self.orientation = [0.0, 0.0, 0.0, 1.0]  # Default quaternion for no rotation

    def leg_positions_callback(self, msg):
        # Update leg positions from the Point[] message
        self.leg_positions = np.array([[p.x, p.y, p.z] for p in msg])

    def imu_callback(self, msg):
        # Update orientation of the robot body
        self.orientation = [msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z, msg.pose.orientation.w]

    def foot_switch_callback(self, msg, leg_idx):
        # Update foot contact state
        self.foot_contacts[leg_idx] = msg.data

    def calculate_com(self):
        # Validate data availability
        if len(self.leg_positions) == 0:
            self.get_logger().warn('Leg positions not received yet.')
            return

        # Adjust leg positions based on IMU orientation
        rotation = R.from_quat(self.orientation)
        imu_to_com_offset = rotation.apply(self.imu_offset)

        # Shift leg positions to account for IMU offset
        adjusted_leg_positions = self.leg_positions - imu_to_com_offset

        # Filter active legs (in contact with the ground)
        active_leg_positions = adjusted_leg_positions[np.array(self.foot_contacts)]

        # Include body center (assumed to be at self.body_com)
        all_positions = np.vstack([self.body_com, active_leg_positions])

        # Calculate approximate CoM as the geometric center
        approx_com = np.mean(all_positions, axis=0)

        # Log the updated CoM
        self.get_logger().info(f'Approximated CoM: {approx_com}')


def main(args=None):
    rclpy.init(args=args)
    node = CoMCalculatorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
