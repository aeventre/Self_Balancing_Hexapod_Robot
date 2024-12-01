cmake_minimum_required(VERSION 3.8)
project(hexapod_com_calculator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pybind11 REQUIRED)


add_library(com_calculator MODULE
    src/com_calculator.cpp
    src/bindings.cpp
)
target_compile_features(com_calculator PRIVATE cxx_std_17)
target_link_libraries(com_calculator PRIVATE pybind11::module)
set_target_properties(com_calculator PROPERTIES PREFIX "" SUFFIX ".so")


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
