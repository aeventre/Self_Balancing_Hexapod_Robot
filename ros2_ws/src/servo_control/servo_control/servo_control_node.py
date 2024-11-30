import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
from adafruit_pca9685 import PCA9685
import busio
import board

class ServoControlNode(Node):
    def __init__(self):
        super().__init__('servo_control_node')

        # Initialize I2C bus
        self.i2c = busio.I2C(board.SCL, board.SDA)

        # Initialize PCA9685 controllers
        self.pca1 = PCA9685(self.i2c, address=0x40)
        self.pca1.frequency = 50

        # Enable second PCA chip by default
        self.declare_parameter('enable_second_pca', True)
        enable_second_pca = self.get_parameter('enable_second_pca').value

        self.pca2 = None
        if enable_second_pca:
            try:
                self.pca2 = PCA9685(self.i2c, address=0x41)
                self.pca2.frequency = 50
                self.get_logger().info("Second PCA chip initialized.")
            except Exception as e:
                self.get_logger().error(f"Failed to initialize second PCA chip: {e}")
        else:
            self.get_logger().info("Second PCA chip disabled.")

        # Subscribe to servo commands
        self.servo_subscription = self.create_subscription(
            Int32MultiArray,
            '/servo_commands',
            self.set_servo_positions,
            10
        )

        self.get_logger().info("Servo Control Node Initialized")

    def set_servo(self, pca, channel, angle):
        """Set a servo to a specific angle."""
        min_pulse = 0.025  # 500 μs
        max_pulse = 0.125  # 2500 μs
        duty_cycle = int(0xFFFF * ((angle / 180) * (max_pulse - min_pulse) + min_pulse))
        pca.channels[channel].duty_cycle = duty_cycle
        self.get_logger().info(f"Channel {channel}: angle={angle}, duty_cycle={duty_cycle}")

    def set_servo_positions(self, msg):
        """Callback to set servo positions based on incoming data."""
        total_channels = 11 if self.pca2 is None else 22
        if len(msg.data) != total_channels:
            self.get_logger().error(f"Expected {total_channels} values, got {len(msg.data)}")
            return

        for i, angle_or_duty in enumerate(msg.data):
            if i < 9:  # Servos on PCA1
                if 0 <= angle_or_duty <= 180:
                    self.set_servo(self.pca1, i, angle_or_duty)
                else:
                    self.get_logger().warning(f"Invalid angle {angle_or_duty} for servo {i}")
            elif self.pca2 and i < 18:  # Servos on PCA2
                if 0 <= angle_or_duty <= 180:
                    self.set_servo(self.pca2, i - 9, angle_or_duty)
                else:
                    self.get_logger().warning(f"Invalid angle {angle_or_duty} for servo {i}")
            elif self.pca2 and i >= 18:  # Extra PWM channels
                if 0 <= angle_or_duty <= 0xFFFF:
                    self.pca2.channels[i - 18].duty_cycle = angle_or_duty
                    self.get_logger().info(f"Set extra PWM {i - 18} to duty cycle {angle_or_duty}")
                else:
                    self.get_logger().warning(f"Invalid duty cycle {angle_or_duty} for extra PWM {i - 18}")

def main(args=None):
    rclpy.init(args=args)
    node = ServoControlNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
