# ROS node creation with c++
3ways to send ros_msgs : Topic, Service, Action Declare Topic, Service, Action in node and build it. <br>
Reference : http://wiki.ros.org/ROS/Tutorials

1) Pkg create
```
$ catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
```

2) Make node_name.cpp
```
$ cd ~/catkin_ws/src/your_pkg/src
$ sudo gedit node_name.cpp
```
Mavros service callreference : https://masoudir.github.io/mavros_tutorial/Chapter1_ArduRover_with_CLI/Step2_How_to_Arm_and_Disarm/

3) Control Drone in SITL with Mavros service, topics
- MODE
There are few mode in Ardupilot : STABILIZE, MANUAL, AUTO, GUIDED, ...
We'll use guided mode to control drone with rosservice.

```
rosservice call /mavros/set_mode "custom_mode: "GUIDED'"
```

- Arming & Disarming
```
arm throttle : Arms the robot
disarm : Disarms the robot
```

- Make move 
```
GUIDED lat lon alt : move vehicle to specified destination
mode HOLD  : stop
```



4) Edit CMakeLists.txt
At the end of the CMakeLists.txt, you should add dependencies
```
add_executable(node_name src/node_name.cpp)
target_link_libraries(node_name ${catkin_LIBRARIES})
add_dependencies(node_name package_name_${catkin_EXPORTED_TARGETS})
```

5) catkin build 
```
$ cd ~/catkin_ws/
$ catkin build
```

6) Run node with rosrun or roslaunch
If you want to use roslaunch, you should make directory "launch" and edit "launch.xml"
```
$ roslaunch package_name node_name
```

---
#### 구현해야 할 것들
- Control : arming, takeoff(height), setposition(move), Circular move, RTL(come home)
- 키입력 받는 부분 함수로 작성
- roslaunch로 작동되게 수정 (지금은 rosrun)
