cmake_minimum_required(VERSION 3.8)
project(kinematics)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Find required libraries (for Matplotlib-C++)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

# Define the executable
add_executable(kinematics
    src/main.cpp
    src/SpiderLeg.cpp
    src/Visualization.cpp
)

# Link Python library
target_link_libraries(kinematics Python3::Python)