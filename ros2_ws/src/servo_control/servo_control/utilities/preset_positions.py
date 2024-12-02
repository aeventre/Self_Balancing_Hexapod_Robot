import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
import time


class ServoController(Node):
    def __init__(self):
        super().__init__('servo_controller')
        self.publisher = self.create_publisher(Int32MultiArray, '/servo_commands', 10)

        # Define positions and emotes
        self.positions = {
            "neutral": [90] * 18,  # All servos at 90 degrees
            "sitting": [45, 45, 45, 45, 45, 45, 45, 45, 45,  # PCA1
                        45, 45, 45, 45, 45, 45, 45, 45, 45],  # PCA2
            "standing": [90, 90, 90, 90, 90, 90, 90, 90, 90,  # PCA1
                         90, 90, 90, 90, 90, 90, 90, 90, 90],  # PCA2
            "wave": [90, 90, 180, 90, 90, 90, 90, 90, 90,  # PCA1 (waving leg 2)
                     90, 90, 90, 90, 90, 90, 90, 90, 90]   # PCA2
        }

        # Start the interactive menu
        self.run_menu()

    def run_menu(self):
        """Display the interactive menu to select positions or transitions."""
        while True:
            try:
                print("\nServo Controller Menu:")
                print("1. Move to Neutral Position")
                print("2. Move to Sitting Position")
                print("3. Move to Standing Position")
                print("4. Perform Sit-to-Stand Transition")
                print("5. Perform Wave Emote")
                print("6. Exit")

                choice = input("Enter your choice: ")

                if choice == '1':
                    self.publish_positions(self.positions["neutral"])
                    print("Moved to Neutral Position.")

                elif choice == '2':
                    self.publish_positions(self.positions["sitting"])
                    print("Moved to Sitting Position.")

                elif choice == '3':
                    self.publish_positions(self.positions["standing"])
                    print("Moved to Standing Position.")

                elif choice == '4':
                    self.sit_to_stand()

                elif choice == '5':
                    self.publish_positions(self.positions["wave"])
                    print("Performed Wave Emote.")

                elif choice == '6':
                    print("Exiting Servo Controller.")
                    break

                else:
                    print("Invalid choice. Please try again.")

            except KeyboardInterrupt:
                print("\nExiting Servo Controller.")
                break
            except Exception as e:
                self.get_logger().error(f"Error: {e}")

    def sit_to_stand(self):
        """Perform a smooth sit-to-stand transition."""
        print("Performing Sit-to-Stand Transition...")
        current_position = self.positions["sitting"][:]
        standing_position = self.positions["standing"]
        steps = 10  # Number of transition steps

        for step in range(1, steps + 1):
            # Interpolate each servo position
            for i in range(len(current_position)):
                current_position[i] = self.interpolate(
                    self.positions["sitting"][i],
                    standing_position[i],
                    step,
                    steps
                )

            # Publish the intermediate position
            self.publish_positions(current_position)
            self.get_logger().info(f"Transition step {step}/{steps}: {current_position}")
            time.sleep(0.5)  # Wait for 0.5 seconds between steps

        print("Transition Complete. Robot is now Standing.")

    def interpolate(self, start, end, step, total_steps):
        """Linearly interpolate between start and end over a number of steps."""
        return int(start + (end - start) * (step / total_steps))

    def publish_positions(self, positions):
        """Publish servo positions to the /servo_commands topic."""
        msg = Int32MultiArray()
        msg.data = positions
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    controller = ServoController()
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()
