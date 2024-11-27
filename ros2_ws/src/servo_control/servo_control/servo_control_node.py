import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
from adafruit_pca9685 import PCA9685
import busio
import board

class ServoControlNode(Node):
    def __init__(self):
        super().__init__('servo_control_node')

        # Declare a parameter to enable or disable the second PCA9685
        self.declare_parameter('enable_second_pca', False)
        enable_second_pca = self.get_parameter('enable_second_pca').value

        self.get_logger().info(f"Initializing Servo Control Node (Second PCA Enabled: {enable_second_pca})")

        # Initialize I2C bus
        self.i2c = busio.I2C(board.SCL, board.SDA)

        # Initialize the first PCA9685
        self.pca1 = PCA9685(self.i2c, address=0x40)
        self.pca1.frequency = 50  # Standard servo frequency

        # Initialize the second PCA9685 if enabled
        self.pca2 = None
        if enable_second_pca:
            self.pca2 = PCA9685(self.i2c, address=0x41)
            self.pca2.frequency = 50

        # Subscribe to servo commands (18 for leg servos, 4 extra channels)
        self.servo_subscription = self.create_subscription(
            Int32MultiArray,
            '/servo_commands',
            self.set_servo_positions,
            10
        )

        self.get_logger().info("Servo Control Node Initialized")

    def set_servo_positions(self, msg):
        total_channels = 11 if self.pca2 is None else 22
        if len(msg.data) != total_channels:
            self.get_logger().error(f"Expected {total_channels} values, got {len(msg.data)}")
            return

        for i, angle_or_duty in enumerate(msg.data):
            if i < 9:  # First 9 channels are for servos on PCA1
                if 0 <= angle_or_duty <= 180:
                    duty_cycle = int(0xFFFF * ((angle_or_duty / 180) * 0.05 + 0.075))
                    self.pca1.channels[i].duty_cycle = duty_cycle
                    self.get_logger().info(f"Set servo {i} on PCA1 to angle {angle_or_duty}")
                else:
                    self.get_logger().warning(f"Invalid angle {angle_or_duty} for servo {i}")
            elif self.pca2 and i < 18:  # Next 9 channels are for servos on PCA2
                if 0 <= angle_or_duty <= 180:
                    duty_cycle = int(0xFFFF * ((angle_or_duty / 180) * 0.05 + 0.075))
                    self.pca2.channels[i - 9].duty_cycle = duty_cycle
                    self.get_logger().info(f"Set servo {i - 9} on PCA2 to angle {angle_or_duty}")
                else:
                    self.get_logger().warning(f"Invalid angle {angle_or_duty} for servo {i}")
            elif self.pca2 and i >= 18:  # Extra PWM channels on PCA2
                if 0 <= angle_or_duty <= 0xFFFF:
                    self.pca2.channels[i - 18].duty_cycle = angle_or_duty
                    self.get_logger().info(f"Set extra PWM {i - 18} on PCA2 to duty cycle {angle_or_duty}")
                else:
                    self.get_logger().warning(f"Invalid duty cycle {angle_or_duty} for extra PWM {i - 18}")

def main(args=None):
    rclpy.init(args=args)
    node = ServoControlNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
