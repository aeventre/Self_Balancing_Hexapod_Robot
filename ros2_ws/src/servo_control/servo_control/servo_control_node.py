import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
from adafruit_pca9685 import PCA9685
import busio
import board
import os
import json

class ServoControlNode(Node):
    def __init__(self):
        super().__init__('servo_control_node')

        # Path to the offsets file
        self.offsets_file = os.path.join(os.path.dirname(__file__), 'servo_offsets.json')
        self.get_logger().info(f"Using offsets file: {self.offsets_file}")

        # Load offsets
        self.offsets = self.load_offsets()

        # Initialize I2C bus
        self.i2c = busio.I2C(board.SCL, board.SDA)

        # Initialize PCA9685 controllers
        self.pca1 = PCA9685(self.i2c, address=0x40)  # First PCA chip
        self.pca1.frequency = 50

        self.pca2 = PCA9685(self.i2c, address=0x41)  # Second PCA chip
        self.pca2.frequency = 50

        # Subscribe to servo commands
        self.servo_subscription = self.create_subscription(
            Int32MultiArray,
            '/servo_commands',
            self.set_servo_positions,
            10
        )

        self.get_logger().info("Servo Control Node Initialized")

    def load_offsets(self):
        """Load servo offsets from the file."""
        try:
            with open(self.offsets_file, 'r') as f:
                return json.load(f)
        except FileNotFoundError:
            self.get_logger().warning("Offsets file not found. Initializing with zeros.")
            return {str(i): 0 for i in range(18)}  # Default 18 channels

    def save_offsets(self):
        """Save servo offsets to the file."""
        with open(self.offsets_file, 'w') as f:
            json.dump(self.offsets, f)
        self.get_logger().info("Offsets saved.")

    def set_servo(self, pca, channel, angle):
        """Set a servo to a specific angle, applying offsets."""
        # Apply the offset for this channel
        offset = self.offsets.get(str(channel), 0)
        angle_with_offset = angle + offset

        # Clamp the angle to the valid range
        angle_with_offset = max(0, min(180, angle_with_offset))

        # Calculate the duty cycle for the desired angle
        min_pulse = 0.025  # 500 μs
        max_pulse = 0.125  # 2500 μs
        duty_cycle = int(0xFFFF * ((angle_with_offset / 180) * (max_pulse - min_pulse) + min_pulse))

        # Set the servo position
        pca.channels[channel].duty_cycle = duty_cycle
        self.get_logger().info(f"Channel {channel}: angle={angle} (offset={offset}, duty_cycle={duty_cycle})")

    def set_servo_positions(self, msg):
        """Callback to set servo positions based on incoming data."""
        total_channels = 18  # 18 servo channels
        if len(msg.data) != total_channels:
            self.get_logger().error(f"Expected {total_channels} values, got {len(msg.data)}")
            return

        for i, angle in enumerate(msg.data):
            if i < 9:  # Servos on PCA1
                if 0 <= angle <= 180:
                    self.set_servo(self.pca1, i, angle)
                else:
                    self.get_logger().warning(f"Invalid angle {angle} for servo {i} on PCA1.")
            elif i < 18:  # Servos on PCA2
                if 0 <= angle <= 180:
                    self.set_servo(self.pca2, i - 9, angle)
                else:
                    self.get_logger().warning(f"Invalid angle {angle} for servo {i} on PCA2.")
            else:
                self.get_logger().error(f"Invalid channel {i}. Must be 0-17.")

def main(args=None):
    rclpy.init(args=args)
    node = ServoControlNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
