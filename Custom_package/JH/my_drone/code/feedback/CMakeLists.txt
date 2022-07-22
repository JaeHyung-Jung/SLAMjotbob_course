cmake_minimum_required(VERSION 3.0.2)
project(drone_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  mavros_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs mavros_msgs
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(DRONE_CONTROL_FILES   "src/drone_control.cpp")

add_library(drone_control_lib     "${DRONE_CONTROL_FILES}")
add_dependencies(drone_control_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_executable(drone_control src/main.cpp)


target_link_libraries(
  drone_control_lib
  PUBLIC
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)

target_link_libraries(
  drone_control 
  PUBLIC
  drone_control_lib
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)