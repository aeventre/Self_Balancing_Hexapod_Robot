cmake_minimum_required(VERSION 3.8)
project(support_polygon_calculator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Find additional libraries
find_package(CGAL REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)

# Add the executable
add_executable(support_polygon_calculator src/support_polygon_calculator.cpp)

# Include directories for the project and libraries
target_include_directories(support_polygon_calculator PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  ${CGAL_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(support_polygon_calculator
  ${CGAL_LIBRARIES}
  ${Boost_LIBRARIES}
)
ament_target_dependencies(support_polygon_calculator rclcpp)

# Require C99 and C++17
target_compile_features(support_polygon_calculator PUBLIC c_std_99 cxx_std_17)

# Install the executable
install(TARGETS support_polygon_calculator
  DESTINATION lib/${PROJECT_NAME})

# Enable testing if necessary
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Skip linter warnings for missing copyright/license
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
