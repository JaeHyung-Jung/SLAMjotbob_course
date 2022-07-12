# ROS node creation with c++
3ways to send ros_msgs : Topic, Service, Action
Declare Topic, Service, Action in node and build it.
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

3) Edit CMakeLists.txt
At the end of the CMakeLists.txt, you should add dependencies
```
add_executable(node_name src/node_name.cpp)
target_link_libraries(node_name ${catkin_LIBRARIES})
add_dependencies(node_name package_name_${catkin_EXPORTED_TARGETS})
```

4) catkin build 
```
$ cd ~/catkin_ws/
$ catkin build
```

5) Run node with rosrun or roslaunch
If you want to use roslaunch, you should make directory "launch" and edit "launch.xml"
```
$ roslaunch package_name node_name
```
