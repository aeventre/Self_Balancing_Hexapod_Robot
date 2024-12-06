import rclpy
from rclpy.node import Node
from hexapod_msgs.msg import LegPositions, FootStatus  # Custom messages
from geometry_msgs.msg import Point, PoseStamped  # CoM and IMU data
import numpy as np
from scipy.spatial.transform import Rotation as R


class CoMCalculatorNode(Node):
    def __init__(self):
        super().__init__('com_calculator_node')

        # Robot parameters
        self.num_legs = 6  # Number of legs
        self.foot_positions = np.zeros((self.num_legs, 3))  # Foot positions (x, y, z)
        self.foot_status = [False] * self.num_legs  # Contact states
        self.body_com = np.array([0.0, 0.0, 0.0])  # Approximate CoM at robot center
        self.imu_offset = np.array([-0.012, 0.0, 0.03])  # IMU offset in meters

        # IMU orientation (quaternion)
        self.orientation = [0.0, 0.0, 0.0, 1.0]  # Default quaternion (no rotation)

        # Subscribers
        self.foot_positions_sub = self.create_subscription(
            LegPositions,
            '/foot_positions',
            self.foot_positions_callback,
            10
        )

        self.foot_status_sub = self.create_subscription(
            FootStatus,
            '/foot_status',
            self.foot_status_callback,
            10
        )

        self.imu_sub = self.create_subscription(
            PoseStamped,
            '/imu/data',
            self.imu_callback,
            10
        )

        # Publisher
        self.com_pub = self.create_publisher(Point, '/center_of_mass', 10)

        # Timer to compute CoM periodically
        self.timer = self.create_timer(0.1, self.calculate_com)

    def foot_positions_callback(self, msg):
        """Update foot positions from LegPositions message."""
        self.foot_positions = np.array([[p.x, p.y, p.z] for p in msg.positions])
        self.get_logger().debug(f'Updated foot positions: {self.foot_positions}')

    def foot_status_callback(self, msg):
        """Update foot contact states from FootStatus message."""
        self.foot_status = list(msg.data)
        self.get_logger().debug(f'Updated foot statuses: {self.foot_status}')

    def imu_callback(self, msg):
        """Update orientation from IMU PoseStamped message."""
        self.orientation = [
            msg.pose.orientation.x,
            msg.pose.orientation.y,
            msg.pose.orientation.z,
            msg.pose.orientation.w,
        ]
        self.get_logger().debug(f'Updated IMU orientation: {self.orientation}')

    def calculate_com(self):
        """Calculate the Center of Mass (CoM)."""
        if not np.any(self.foot_status):
            self.get_logger().warn('No feet are in contact with the ground. Cannot calculate CoM.')
            return

        try:
            # Apply IMU offset and orientation adjustment
            rotation = R.from_quat(self.orientation)
            imu_to_com_offset = rotation.apply(self.imu_offset)

            # Adjust foot positions based on IMU offset
            adjusted_foot_positions = self.foot_positions - imu_to_com_offset

            # Select only active feet
            active_positions = adjusted_foot_positions[np.array(self.foot_status)]

            if active_positions.size == 0:
                self.get_logger().warn('No active feet positions available for CoM calculation.')
                return

            # Include body CoM (robot center) for computation
            all_positions = np.vstack([self.body_com, active_positions])

            # Compute approximate CoM as the mean of all contributing points
            approx_com = np.mean(all_positions, axis=0)

            # Log and publish the calculated CoM
            self.get_logger().info(
                f'Calculated CoM from {len(active_positions)} active feet: '
                f'x={approx_com[0]}, y={approx_com[1]}, z={approx_com[2]}'
            )
            com_msg = Point(x=approx_com[0], y=approx_com[1], z=approx_com[2])
            self.com_pub.publish(com_msg)

        except ValueError as e:
            self.get_logger().error(f'Error in IMU orientation processing: {e}')
        except Exception as e:
            self.get_logger().error(f'Unexpected error in CoM calculation: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = CoMCalculatorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
