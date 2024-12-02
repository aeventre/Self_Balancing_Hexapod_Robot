# SpiderBot

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


