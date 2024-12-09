# Software Design

**OS:** Ubuntu 24.04 "noble"  
**Framework:** Ros2  
**Distro:** Jazzy  

## Table of Contents

- [Software Design](#software-design)
  - [Table of Contents](#table-of-contents)
  - [Instructions for Running the Software on the Pi](#instructions-for-running-the-software-on-the-pi)
    - [**1. Setting Up the Virtual Environment**](#1-setting-up-the-virtual-environment)
  - [ROS2 Package Overview](#ros2-package-overview)
    - [1. **Support Polygon Calculator**](#1-support-polygon-calculator)
    - [2. **Servo Control**](#2-servo-control)
    - [3. **IMU Interface**](#3-imu-interface)
    - [4. **Foot Sensor Package**](#4-foot-sensor-package)
    - [5. **Static Balancing Package**](#5-static-balancing-package)
    - [6. **Inverse and Forward Kinematics Package**](#6-inverse-and-forward-kinematics-package)
    - [7. **Center of Mass Calculator Package**](#7-center-of-mass-calculator-package)
  - [ROS2 Topic List](#ros2-topic-list)

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
