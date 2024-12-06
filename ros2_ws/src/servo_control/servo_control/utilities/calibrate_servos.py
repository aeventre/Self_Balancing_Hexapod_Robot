import rclpy
from rclpy.node import Node
from adafruit_pca9685 import PCA9685
import busio
import board
import json

class ServoCalibration(Node):
    def __init__(self):
        super().__init__('servo_calibration')

        # Path to servo_offsets.json in the servo_control package
        self.get_logger().info("Initializing Servo Calibration...")
        self.offsets_file = os.path.join(os.path.dirname(__file__), 'servo_offsets.json')
        self.get_logger().info(f"Using offsets file: {self.offsets_file}")

        # Load or initialize servo offsets
        self.offsets = self.load_offsets()

        # Initialize I2C bus
        self.i2c = busio.I2C(board.SCL, board.SDA)

        # Initialize PCA9685 boards
        self.pca1 = PCA9685(self.i2c, address=0x40)  # First board
        self.pca1.frequency = 50

        self.pca2 = PCA9685(self.i2c, address=0x41)  # Second board
        self.pca2.frequency = 50

        # Start interactive calibration
        self.calibrate()

    def load_offsets(self):
        """Load servo offsets from a file."""
        try:
            with open(self.offsets_file, 'r') as f:
                return json.load(f)
        except FileNotFoundError:
            self.get_logger().warning("Offsets file not found. Initializing with zeros.")
            return {str(i): 0 for i in range(18)}  # Default 18 channels

    def save_offsets(self):
        """Save servo offsets to a file."""
        with open(self.offsets_file, 'w') as f:
            json.dump(self.offsets, f)
        self.get_logger().info("Offsets saved.")

    def set_servo(self, channel, angle):
        """Set a servo to a specific angle."""
        offset = self.offsets.get(str(channel), 0)
        angle_with_offset = angle + offset

        # Ensure the angle is within the valid range
        angle_with_offset = max(0, min(180, angle_with_offset))

        # Calculate the duty cycle for the adjusted angle
        min_pulse = 0.025  # 500 μs
        max_pulse = 0.125  # 2500 μs
        duty_cycle = int(0xFFFF * ((angle_with_offset / 180) * (max_pulse - min_pulse) + min_pulse))

        # Determine which PCA board and channel to use
        if channel < 9:
            self.pca1.channels[channel].duty_cycle = duty_cycle
        elif channel < 18:
            self.pca2.channels[channel - 9].duty_cycle = duty_cycle
        else:
            self.get_logger().error(f"Invalid channel {channel}. Must be 0-17.")

        self.get_logger().info(f"Channel {channel}: angle={angle} (offset={offset}, duty_cycle={duty_cycle})")

    def calibrate(self):
        """Interactive calibration routine."""
        current_channel = None

        while True:
            try:
                print("\nServo Calibration Menu:")
                if current_channel is not None:
                    print(f"Currently selected channel: {current_channel}")
                print("1. Select Servo Channel (0-17)")
                print("2. Set Servo Angle")
                print("3. Adjust Offset")
                print("4. Save Offsets")
                print("5. Exit")

                choice = input("Enter your choice: ")

                if choice == '1':
                    current_channel = int(input("Enter servo channel (0-17): "))
                    print(f"Selected channel {current_channel}.")

                elif choice == '2':
                    if current_channel is None:
                        print("Please select a servo channel first.")
                        continue
                    angle = int(input("Enter angle (0-180): "))
                    self.set_servo(current_channel, angle)

                elif choice == '3':
                    if current_channel is None:
                        print("Please select a servo channel first.")
                        continue
                    offset = int(input("Enter offset (-90 to 90): "))
                    self.offsets[str(current_channel)] = offset
                    print(f"Offset for channel {current_channel} set to {offset}.")

                elif choice == '4':
                    self.save_offsets()

                elif choice == '5':
                    print("Exiting calibration.")
                    break

                else:
                    print("Invalid choice. Please try again.")

            except KeyboardInterrupt:
                print("\nExiting calibration.")
                break
            except Exception as e:
                self.get_logger().error(f"Error: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = ServoCalibration()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
