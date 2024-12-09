# Self-Balacing Hexapod Robot
Created by: **Alec Ventresca & Ella Hicks**  

***NOTE: The kinematics package NOT currently functional.** All the rest of the packages have been tested and are functional. The only reason it has been pushed to main is to submit this for our mechatronics class*

![20241202_131742](https://github.com/user-attachments/assets/5de234e7-d59f-4bf5-8e5d-8d2eb02bb3d5)



## Table of Contents



## Overview
This robot was created to be a platform for us to learn and experiment with various types of sensors and gaits as well as learn the ROS2 framework. Modularity is a large component of this design both hardware and software wise so different sensors can be added and removed without needing to change the core design of the robot. Currently this is just the core of the robot and we intend to add more sensor and package configurations in the future!  

The goal for the initial configuration of this project was to design a Hexapod Robot capable of performing dynamic movements and maintaining self-balance. The robot demonstrates the integration of mechanical and electronic systems and software packages to achieve autonomous and stable locomotion. The hexapod robot features a Raspberry Pi 4b as the central processing unit. It relies on ROS 2 Jazzy to manage the communication and control across the robot's various components. Each package communication ensures continuous data exchange between the packages for dynamic adjustments. The key objectives of the hexapod include the following:

1. Ensuring the robot can walk and move dynamically.
2. Incorporating real-time balancing mechanisms to keep the robot functional and upright under various conditions.
3. Develop modular software packages for control, movement computation, and sensing.
4. Utilize ROS 2 Jazzy to coordinate the robot's operations.

### Future Ideas/Plans
In no particular order:
1. Getting the kinematics package to actually work
2. Getting it to map out a room with a lidar sensor
3. Experimenting with different gaits, a quadraped "attack" mode seems hard but would be funny
4. Adding a Pi cam and learning opencv to have it recognize and chase people
5. Rough terrain navigation


## Acknowledgments
All CAD models used are from "Robs Tech Workbench" at https://github.com/robs-tech-workbench/hexapod_spiderbot_model\  
  
Shoutout to Addison Sears-Collins for all the incredibly helpful ROS2 tutorials at https://automaticaddison.com/


# Software Design

**OS:** Ubuntu 24.04 "noble"  
**Framework:** Ros2  
**Distro:** Jazzy  

ROS2 Package Structure:  
![Support Polygon](https://github.com/user-attachments/assets/2a590f97-79df-4a50-9e1c-7e0ff6e2a661)

## Instructions for Running the Software on the Pi
### **1. Setting Up the Virtual Environment**

1. Clone the repository:
   ```bash
   git clone https://github.com/aeventre/SpiderBot.git
   cd SpiderBot/ros2_ws
2. Run the setup script, this will create the environment an install all the python dependencies
    ```bash
    ./setup.sh
3. Build the ROS2 workspace
    ```bash
    cd ros2_ws
    colcon build
4. In a New Terminal Source the workspace
    ```bash
    source ros2_ws/install/setup.bash

### **2. Commands for Running Nodes**

- **Support Polygon Calculator**:  
  ```bash
  ros2 launch support_polygon_calculator support_polygon_calculator.launch.py
  ```  

- **Servo Control**:  
  ```bash
  ros2 launch servo_control servo_control.launch.py
  ```  

- **IMU Interface**:  
  ```bash
  ros2 launch imu_interface imu_interface.launch.py
  ```  

- **Foot Sensor Package**:  
  ```bash
  ros2 launch foot_sensor foot_sensor.launch.py
  ```  

- **Static Balancing Package**:  
  ```bash
  ros2 launch static_balancer static_balancer.launch.py
  ```  
## ROS2 Package Overview
### 1. **Support Polygon Calculator**
- **Purpose**:  
  Calculates the support polygon, centroid, and stability margin based on grounded foot positions and the center of mass (CoM).

- **Key Components**:  
  - `support_polygon_calculator.cpp`: Implements the core logic for polygon computation and stability margin calculation.  
  - `math_utils.hpp/cpp`: Shared utility functions for geometric and mathematical operations.  
  - `support_polygon_calculator.launch.py`: Simplifies launching the node with appropriate parameters.  

- **Subscribed Topics**:  
  - `/grounded_foot_positions` (geometry_msgs/Polygon): Foot positions currently in contact with the ground.  
  - `/center_of_mass` (geometry_msgs/Point): CoM position of the robot.  

- **Published Topics**:  
  - `/support_polygon` (geometry_msgs/PolygonStamped): The computed support polygon.  
  - `/polygon_centroid` (geometry_msgs/Point): Centroid of the support polygon.  
  - `/stability_margin` (std_msgs/Float32): Stability margin of the robot.  

---

### 2. **Servo Control**
- **Purpose**:  
  Controls the servos to execute gait transitions and posture adjustments.

- **Key Components**:  
  - `servo_controller.cpp`: Implements PWM signal generation and servo control logic.  
  - `servo_settings.yaml`: Configures servo-specific parameters like offsets, limits, and joint IDs.  
  - `servo_control.launch.py`: Launch file for easy startup.  

- **Subscribed Topics**:  
  - `/trajectory_commands` (custom or std_msgs): Commands for joint positions or PWM values.  

- **Published Topics**:  
  - None (controls servos directly).  

---

### 3. **IMU Interface**
- **Purpose**:  
  Reads IMU data to provide orientation and balance feedback.

- **Key Components**:  
  - `imu_interface.cpp`: Interfaces with the IMU hardware to publish orientation and acceleration data.  
  - `imu_settings.yaml`: Contains filtering parameters and IMU-specific settings.  
  - `imu_interface.launch.py`: Simplifies starting the node.  

- **Published Topics**:  
  - `/imu_data` (sensor_msgs/Imu): Filtered IMU data for other nodes.  

---

### 4. **Foot Sensor Package**
- **Purpose**:  
  Monitors foot contact sensors to determine which feet are grounded.

- **Key Components**:  
  - `foot_sensor.cpp`: Implements sensor reading and contact detection logic.  
  - `foot_sensor.launch.py`: Launch file for the sensor node.  

- **Published Topics**:  
  - `/grounded_foot_positions` (geometry_msgs/Polygon): Positions of grounded feet.  

- **Subscribed Topics**:  
  - None (directly interfaces with sensors).  

---

### 5. **Static Balancing Package**
- **Purpose**:  
  Adjusts the robot's posture to maintain stability when stationary, based on feedback from the support polygon and foot sensors.

- **Key Components**:  
  - `static_balancer.cpp`: Computes joint adjustments to keep the CoM within the support polygon.  
  - `static_balancer.launch.py`: Launch file for the balancing node.

- **Subscribed Topics**:  
  - `/support_polygon` (geometry_msgs/PolygonStamped): The computed support polygon.  
  - `/center_of_mass` (geometry_msgs/Point): Position of the CoM.  
  - `/grounded_foot_positions` (geometry_msgs/Polygon): Positions of grounded feet.  

- **Published Topics**:  
  - `/balancing_commands` (custom or std_msgs): Adjustments for servo control to maintain balance. 

### 6. **Inverse and Forward Kinematics Package**
- **Purpose**:
  The inverse kinematics computes the necessary joint angles for the robot's legs based on the desired leg command. The forward kinematics calculates the positions of the feet based on the current joint angles.
  
- **Key Components**:
  - `ik_node.py`: Subscribes to leg_commands to receive the desired foot positions, computes inverse kinematics to determine the required joint angles and publishes these joint angles to joint_angles.
  - `kinematics.py`: Subscribes to the joint_angles, computes the 3D positions of the feet using forward kinematics, and publishes these positions to the foot_positions topic.

- **Published Topics**:
  - `/joint_angles`: Publishes the computed joint angles as an array. These angles are used by the servo motor controllers to move the robot's legs to the desired positions. (Inverse Kinematics)
  - `/foot_positions`: Publishes the calculated 3D positions of the six feet, with each foot's position represented as [x, y, z]. (Forward Kinematics)
 
- **Subscribed Topics**:
  - `/leg_commands`: Receives an array of target positions for the robot's legs that guide the computation of joint angles needed to achieve the desired foot placements. (Inverse Kinematics)
  - `/joint_angles`: Receives the current joint angles of the hexapod's legs with 3 angles (coxa, femur, tibia) and provides the input data to determine the 3D positions of the robot's feet. (Foward Kinematics)

### 7. **Center of Mass Calculator Package**
- **Purpose**:
  Calculates the robot's center of mass in real-time and shares data with the static_balancer to ensure the center of mass remains within the support polygon.

- **Key Components**:
  - `com_calculator.py`: Calculates and publishes the center of mass of the hexapod robot by combining foot positions, contact statuses, and IMU orientation data, while accounting for the robot's geometry and offset of the IMU.

- **Published Topics**:
  - `/foot_positions`: Provides the 3D positions of each foot.
  - `/foot_status`: Indicates which feet are in contact with the ground.
  - `/imu/data`: Provides the IMU's oreitnation in quaternion format.
 
- **Subscribed Topics**:
  - `/center_of_mass`: Publishes the computed 3D position of the robot's center of mass.

## ROS2 Topic List


1. **`/joint_angles`**
   - **Type**: `hexapod_msgs/JointAngles`
   - **Purpose**: Commands or approximations of joint angles for all servos.

2. **`/foot_status`**
   - **Type**: `std_msgs/Bool[]`
   - **Purpose**: Contact status of each foot (e.g., `true` if the foot is touching the ground).

3. **`/center_of_mass`**
   - **Type**: `geometry_msgs/Point`
   - **Purpose**: Computed center of mass (CoM) of the robot in the body frame or global frame.

4. **`/foot_positions`**
   - **Type**: `hexapod_msgs/LegPositions`
   - **Purpose**: Current Cartesian positions of all feet relative to the robot's body frame.

5. **`/support_polygon`**
   - **Type**: `hexapod_msgs/Polygon`
   - **Purpose**: Polygon formed by the feet in contact with the ground.

6. **`/stability_margin`**
   - **Type**: `std_msgs/Float64`
   - **Purpose**: Stability margin of the robot based on the CoM and support polygon.

7. **`/polygon_centroid`**
   - **Type**: `geometry_msgs/Point`
   - **Purpose**: Centroid of the support polygon, used for stability analysis.

8. **`/leg_commands`**
   - **Type**: `hexapod_msgs/LegCommands`
   - **Purpose**: Desired Cartesian positions or trajectories for the feet, generated by a gait planner or controller.



# Hardware Design
One of the main goals I had for the initial design is to try and keep this robot as modular as possible so that I can mess around with a bunch of different 
things and not be constrained to just the inital configuration. As such the GPIO of the ras pi is still accessible so wires or another PCB could be added. There are also 4 extra PWM outputs from the PCA9685 chips on the PCB that can be used to add additional servos or anything else that could be PWM controlled.

## Structure
All CAD models currently being used are from "Robs Tech Workbench" and can be found at https://github.com/robs-tech-workbench/hexapod_spiderbot_model\  

Since this project is using slightly different hardware to his and additional sensors might be placed on it in the future,some parts of the central body will eventually be modified and that CAD will be uploaded here.

## Electronics

For this project a custom PCB was designed to rest on top of a Raspberry pi 4b in order to make the wiring for everything neater and because PCB design is fun.  

The main chips on the board are:  
- **PCA9685** - Used to create PWM outputs to control the servos, recieves commands from the pi over the I2C bus
- **LSM6DSO32TR** - IMU for sending attitude data to the pi over the I2C bus
- **LM393** - Op-amp that compares the battery voltage to the 5V line and will light up an LED and send a 0 to a GPIO pin when the batteries voltage gets too low

The rest of the chips are for reducing the voltage from the battery to a 5V 3 amp max line and a 6V 20 amp max line. The 6V line is for powering the servos which tend to draw a lot of current. I do not expect 20 amps to ever get drawn on that line, it's about 3 just standing, and then I'd imagine 10 amps max when walking, but better safe then sorry.

## Setting the I2C Address of the PCA9685  
The I2C address of the PCA chips is determined by certain pin  

From datasheet:  
![image](https://github.com/user-attachments/assets/077c3241-b36b-435b-8d50-6b18a9e48571)

JP1-JP6 on the back of the PCB correlates to A0-A5 for chip 1 (left side) and JP7-JP12 correlates to chip 2 (right side). Placing a
jumper on the pin will bring it high and change the I2C address accordingly.  

Currently the code is configured for a jumper placed on JP7. The address can be edited in the servo_control packages code.

## PCB Layout
Front:   
![image](https://github.com/user-attachments/assets/dfdeaa73-c6c8-46eb-a4a2-f4136d9daac4)
  
Back:  
![image](https://github.com/user-attachments/assets/7bdfb4ab-2f1f-43e5-bcb4-fd6b4d70a6b0)