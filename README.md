# Self-Balacing Hexapod Robot
Created by: **Alec Ventresca & Ella Hicks**  

***NOTE: The kinematics package NOT currently functional.** All the rest of the packages have been tested and are functional. The only reason it has been pushed to main is to submit this for our mechatronics class*

![20241202_131742](https://github.com/user-attachments/assets/5de234e7-d59f-4bf5-8e5d-8d2eb02bb3d5)



## Table of Contents
 - **[Self-Balacing Hexapod Robot](#self-balacing-hexapod-robot)**
   - [Overview](#overview)
   - [Future Ideas/Plans](#future-ideas)
   - [Acknowledgments](#acknowledgments) 
- [**Software Design**](ros2_ws/README.md)
  - [Overview](ros2_ws/README.md#overview)
  - [Instructions for Running the Software on the Pi](ros2_ws/README.md#instructions-for-running-the-software-on-the-pi)
    - [1. Setting Up the Virtual Environment](ros2_ws/README.md#1-setting-up-the-virtual-environment)
    - [2. Commands for Running Nodes](ros2_ws/README.md#2-commands-for-running-nodes)
  - [ROS2 Package Overview](ros2_ws/README.md#ros2-package-overview)
    - [1. Support Polygon Calculator](ros2_ws/README.md#1-support-polygon-calculator)
    - [2. Servo Control](ros2_ws/README.md#2-servo-control)
    - [3. IMU Interface](ros2_ws/README.md#3-imu-interface)
    - [4. Foot Sensor Package](ros2_ws/README.md#4-foot-sensor-package)
    - [5. Static Balancing Package](ros2_ws/README.md#5-static-balancing-package)
    - [6. Inverse and Forward Kinematics Package](ros2_ws/README.md#6-inverse-and-forward-kinematics-package)
    - [7. Center of Mass Calculator Package](ros2_ws/README.md#7-center-of-mass-calculator-package)
  - [ROS2 Topic List](ros2_ws/README.md#ros2-topic-list)
- [**Hardware Design**](hardware/README.md) 
  - [Overview](hardware/README.md#overview)
  - [Structure](hardware/README.md#structure)
  - [Electronics](hardware/README.md#electronics)
    - [Setting the I2C Address of the PCA9685](hardware/README.md#setting-the-i2c-address-of-the-pca9685)
  - [PCB Layout](hardware/README.md#pcb-layout)


## Overview
This robot was created to be a platform for us to learn and experiment with various types of sensors and gaits as well as learn the ROS2 framework. Modularity is a large component of this design both hardware and software wise so different sensors can be added and removed without needing to change the core design of the robot. Currently this is just the core of the robot and we intend to add more sensor and package configurations in the future!  

The goal for the initial configuration of this project was to design a Hexapod Robot capable of performing dynamic movements and maintaining self-balance. The robot demonstrates the integration of mechanical and electronic systems and software packages to achieve autonomous and stable locomotion. The hexapod robot features a Raspberry Pi 4b as the central processing unit. It relies on ROS 2 Jazzy to manage the communication and control across the robot's various components. Each package communication ensures continuous data exchange between the packages for dynamic adjustments. The key objectives of the hexapod include the following:

1. Ensuring the robot can walk and move dynamically.
2. Incorporating real-time balancing mechanisms to keep the robot functional and upright under various conditions.
3. Develop modular software packages for control, movement computation, and sensing.
4. Utilize ROS 2 Jazzy to coordinate the robot's operations.

### Future Ideas
In no particular order:
1. Getting the kinematics package to actually work
2. Getting it to map out a room with a lidar sensor
3. Experimenting with different gaits, a quadraped "attack" mode seems hard but would be funny
4. Adding a Pi cam and learning opencv to have it recognize and chase people
5. Rough terrain navigation


## Acknowledgments
All CAD models used are from "Robs Tech Workbench" at https://github.com/robs-tech-workbench/hexapod_spiderbot_model\  
  
Shoutout to Addison Sears-Collins for all the incredibly helpful ROS2 tutorials at https://automaticaddison.com/


