# Software Design

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

---

## How to Use

### **1. Build the Workspace**

```bash
cd ros2_ws
colcon build
source install/setup.bash
```

### **2. Run Nodes**

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

---

## Future Improvements

- Add RViz visualization for debugging (e.g., display support polygons, CoM, and stability margin).  
- Implement advanced filtering for IMU data (e.g., complementary or Kalman filters).  
- Introduce ROS2 actions in `servo_control` for trajectory planning and execution.  
- Expand gait options (e.g., dynamic tripod gait transitions).  

---

This structure focuses on explaining **what each package does, its key topics, and its relationship to the system**, while also providing instructions for usage. Let me know if there’s anything else you’d like to refine! 🚀
