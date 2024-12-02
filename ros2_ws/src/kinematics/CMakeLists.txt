cmake_minimum_required(VERSION 3.8)
project(kinematics)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Find required libraries (for Matplotlib-C++)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Define the executable
add_executable(forward_kinematics_node
    src/forward_kinematics_node.cpp 
    src/SpiderLeg.cpp
    src/Hexapod.cpp
)
target_link_libraries(forward_kinematics_node ${rclcpp_LIBRARIES})
ament_target_dependencies(forward_kinematics_node
    rclcpp
    std_msgs
)

add_executable(inverse_kinematics_node
    src/inverse_kinematics_node.cpp 
    src/SpiderLeg.cpp 
    src/Hexapod.cpp 
)
target_link_libraries(inverse_kinematics_node ${rclcpp_LIBRARIES})
ament_target_dependencies(inverse_kinematics_node
    rclcpp 
    std_msgs 
)

install(TARGETS 
    forward_kinematics_node
    inverse_kinematics_node
    DESTINATION lib/${kinematics}
)

install(DIRECTORY 
    launch/
    DESTINATION share/${kinematics}/launch
)

install (DIRECTORY 
    include/
    DESTINATION include/
)

ament_package()