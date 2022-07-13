# ROS node creation with c++
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

#### MODE
There are few mode in Ardupilot : STABILIZE, MANUAL, AUTO, GUIDED, ... 
mode control with Ardupilot custom mode : http://wiki.ros.org/mavros/CustomModes

For example : set mode to GUIDED mode
```
#include <mavros_msgs/SetMode.h> // include

  ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode> 
                ("mavros/set_mode");
                              
  mavros_msgs::SetMode jh_set_mode_guided;
  jh_set_mode_guided.request.custom_mode = "GUIDED";
  
  int main(...)
  {
      ~~~
      set_mode_client.call(jh_set_mode_guided); // service call 
  }
                
```

#### Arming 
```
#include <mavros_msgs/CommandBool.h>

    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
                ("mavros/cmd/arming");
                
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;
    
    int main(...)
    {
                    arming_client.call(arm_cmd); // arming service call
    }
                
```


#### Movement
There are many ways to make movement : global_position, local_position, setpoint_position
Reference : [Mavros wiki](http://wiki.ros.org/action/fullsearch/mavros?action=fullsearch&context=180&value=linkto%3A%22mavros%22)
##### global_position
-
-
-

##### local_position
reference : [standard local position.cpp](http://docs.ros.org/en/lunar/api/mavros/html/local__position_8cpp_source.html)
- local_position/pose
- local_position/velocity
- etc

##### setpoint_position
- setpoint_position/global
- setpoint_position/local

4) Edit CMakeLists.txt
At the end of the CMakeLists.txt, you should add dependencies
```
add_executable(node_name src/node_name.cpp)
target_link_libraries(node_name ${catkin_LIBRARIES})
add_dependencies(node_name package_name_${catkin_EXPORTED_TARGETS}) // 필요할 때만 사용
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
