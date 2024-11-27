import rclpy
from rclpy.node import Node
from adafruit_pca9685 import PCA9685
import busio
import board
import json

class ServoCalibration(Node):
    def __init__(self):
        super().__init__('servo_calibration')

        self.get_logger().info("Initializing Servo Calibration...")

        # Load or initialize servo offsets
        self.offsets_file = 'servo_offsets.json'
        self.offsets = self.load_offsets()

        # Initialize I2C bus
        self.i2c = busio.I2C(board.SCL, board.SDA)

        # Initialize PCA9685
        self.pca = PCA9685(self.i2c, address=0x40)
        self.pca.frequency = 50  # Standard servo frequency

        # Start interactive calibration
        self.calibrate()

    def load_offsets(self):
        """Load servo offsets from a file."""
        try:
            with open(self.offsets_file, 'r') as f:
                return json.load(f)
        except FileNotFoundError:
            self.get_logger().warning("Offsets file not found. Initializing with zeros.")
            return {str(i): 0 for i in range(16)}  # Default 16 channels

    def save_offsets(self):
        """Save servo offsets to a file."""
        with open(self.offsets_file, 'w') as f:
            json.dump(self.offsets, f)
        self.get_logger().info("Offsets saved.")

    def set_servo(self, channel, angle):
        """Set a servo to a specific angle."""
        offset = self.offsets.get(str(channel), 0)
        angle_with_offset = angle + offset
        if 0 <= angle_with_offset <= 180:
            duty_cycle = int(0xFFFF * ((angle_with_offset / 180) * 0.05 + 0.075))
            self.pca.channels[channel].duty_cycle = duty_cycle
            self.get_logger().info(f"Channel {channel}: angle={angle} (offset={offset})")
        else:
            self.get_logger().warning(f"Angle out of range: {angle_with_offset}")

    def calibrate(self):
        """Interactive calibration routine."""
        while True:
            try:
                print("\nServo Calibration Menu:")
                print("1. Set Servo Angle")
                print("2. Adjust Offset")
                print("3. Save Offsets")
                print("4. Exit")

                choice = input("Enter your choice: ")

                if choice == '1':
                    channel = int(input("Enter servo channel (0-15): "))
                    angle = int(input("Enter angle (0-180): "))
                    self.set_servo(channel, angle)

                elif choice == '2':
                    channel = int(input("Enter servo channel (0-15): "))
                    offset = int(input("Enter offset (-90 to 90): "))
                    self.offsets[str(channel)] = offset
                    print(f"Offset for channel {channel} set to {offset}.")

                elif choice == '3':
                    self.save_offsets()

                elif choice == '4':
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
