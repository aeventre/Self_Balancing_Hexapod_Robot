cmake_minimum_required(VERSION 3.8)
project(support_polygon_calculator)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(CGAL REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)

# Set build type to Release for performance
set(CMAKE_BUILD_TYPE Release)

# Include directories
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CGAL_INCLUDE_DIRS})

# Add library
add_library(support_polygon_calculator
    src/support_polygon_calculator.cpp
)

# Link libraries
target_link_libraries(support_polygon_calculator
    ${Boost_LIBRARIES}
    ${CGAL_LIBRARIES}
)

# Install targets
install(TARGETS support_polygon_calculator
    DESTINATION lib
)
install(DIRECTORY include/
    DESTINATION include
)

# Export package
ament_package()
