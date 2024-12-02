# SpiderBot
import time

def set_servo_positions(self, msg):
    """Callback to set servo positions based on incoming data."""
    total_channels = 18  # 18 servo channels
    self.get_logger().info(f"Received positions: {msg.data}")

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

        # Introduce a small delay between commands
        time.sleep(0.01)  # 10 ms delay



def set_servo(self, pca, channel, angle):
    """Set a servo to a specific angle, applying offsets, and avoid redundant writes."""
    # Apply the offset for this channel
    offset = self.offsets.get(str(channel), 0)
    angle_with_offset = angle + offset
    angle_with_offset = max(0, min(180, angle_with_offset))  # Clamp the angle

    # Calculate the duty cycle
    min_pulse = 0.025  # 500 μs
    max_pulse = 0.125  # 2500 μs
    duty_cycle = int(0xFFFF * ((angle_with_offset / 180) * (max_pulse - min_pulse) + min_pulse))

    # Check if the duty cycle is already set
    if pca.channels[channel].duty_cycle == duty_cycle:
        self.get_logger().debug(f"Channel {channel} already set to {duty_cycle}. Skipping write.")
        return

    # Set the new duty cycle
    pca.channels[channel].duty_cycle = duty_cycle
    self.get_logger().info(f"Channel {channel}: angle={angle} (offset={offset}, duty_cycle={duty_cycle})")



## Testing commands

#IK node:
ros2 topic pub /leg_commands std_msgs/msg/Float32MultiArray "data:
- 0.15
- 0.1
- -0.25
- 0.15
- -0.1
- -0.25
- 0.0
- 0.2
- -0.25
- -0.15
- 0.1
- -0.25
- -0.15
- -0.1
- -0.25
- 0.0
- -0.2
- -0.25"

# FK node
ros2 topic pub /joint_angles std_msgs/msg/Float32MultiArray "data:
- 0.0
- 0.0
- -1.0
- 0.5
- -0.5
- -1.0
- 0.0
- 1.0
- 0.0
- -0.5
- 0.5
- -1.0
- 0.0
- 0.0
- 1.0
- -0.5
- -0.5
- 1.0"


## Ros2 Package Structure
├── ros2_ws/                  # ROS2 workspace
│   ├── src/
│   │   ├── servo_control/       # Servo control package
│   │   ├── imu_driver/          # IMU interface package
│   │   ├── gpio_sensors/        # Ground-contact switches package
│   │   ├── gait_controller/     # Gait generation and walking control
│   │   ├── static_balancer/     # Static balancing algorithms
│   │   ├── dynamic_balancer/    # Dynamic balancing during walking






## Instructions for Setting up the Virtual Environment

1. Clone the repository:
   ```bash
   git clone https://github.com/aeventre/SpiderBot.git
   cd SpiderBot
2. Run the setup script
    ```bash
    ./setup.sh
3. Build the ROS2 workspace
    ```bash
    cd ros2_ws
    colcon build
4. In a New Terminal Source the workspace
    ```bash
    source ros2_ws/install/setup.bash


    
## Useful Resources
CAD from: https://github.com/robs-tech-workbench/hexapod_spiderbot_model

Useful References:
https://docs.ros.org/en/jazzy/Tutorials.html

https://github.com/stevej52/ros2_pca9685?tab=readme-ov-file#ros2_pca9685



Other Hexapods for reference:

https://github.com/robs-tech-workbench/hexapod_spiderbot_tutorials/blob/main/tutorial_tools_hardware_3d_parts_spider_robot/README.md

https://github.com/makeyourpet/hexapod

https://github.com/SmallpTsai/hexapod-v2-7697


