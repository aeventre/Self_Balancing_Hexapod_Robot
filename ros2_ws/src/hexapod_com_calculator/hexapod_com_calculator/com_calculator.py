import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Bool
from hexapod_com_calculator import compute_center_of_mass

class CoMCalculatorNode(Node):
    def __init__(self):
        super().__init__('com_calculator_node')

        # Subscribe to IMU data
        self.imu_subscription = self.create_subscription(
            PoseStamped,
            'imu/data',
            self.imu_callback,
            10
        )

        # Subscribe to foot switch data
        self.foot_switch_subscriptions = [
            self.create_subscription(Bool, f'leg_{i}/foot_switch', self.foot_switch_callback, 10)
            for i in range(6)
        ]

        # Placeholder for received data
        self.imu_orientation = None
        self.foot_switches = [False] * 6

        # Define the timer for periodic CoM calculation
        self.timer = self.create_timer(0.1, self.calculate_com)

    def imu_callback(self, msg):
        # Store IMU orientation (for example: roll, pitch, yaw)
        self.imu_orientation = msg.pose.orientation

    def foot_switch_callback(self, msg):
        # Update which legs are in contact with the ground
        leg_index = int(msg._connection_header['topic'].split('/')[1].split('_')[1])
        self.foot_switches[leg_index] = msg.data

    def calculate_com(self):
        if self.imu_orientation is None:
            self.get_logger().warn('IMU data not received yet.')
            return

        # Define masses and positions
        # Replace these with dynamic inputs from your robot state
        masses = [1.0] * 6
        positions = [[0, 0, 0], [1, 0, 0], [0, 1, 0], [-1, 0, 0], [0, -1, 0], [0, 0, 1]]

        # Filter out legs that are not in contact
        active_masses = [masses[i] for i in range(6) if self.foot_switches[i]]
        active_positions = [positions[i] for i in range(6) if self.foot_switches[i]]

        # Calculate CoM
        com = compute_center_of_mass(active_masses, active_positions)
        self.get_logger().info(f'Calculated CoM: {com}')

def main(args=None):
    rclpy.init(args=args)
    node = CoMCalculatorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
