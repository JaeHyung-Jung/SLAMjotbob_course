### <div align=center> Simulation concept drawing <div>
![image](https://user-images.githubusercontent.com/79160507/178412154-a51bd9bc-619f-41e0-a44e-d2bc7f991e0c.png)

---

### Simulation Sequence
After gazebo, ardupilot, ardupilot_gazebo, mavros installed, start simulating.
    
1) Run gazebo
```
~$ gazebo --verbose ~/ardupilot_gazebo/worlds/iris_arducopter_runway.world
```

2) Run ardupilot
```
$ cd ~/ardupilot/ArduCopter/ && sim_vehicle.py -v ArduCopter -f gazebo-iris --console
```
3) Run mavros 
```
$ roslaunch mavros apm.launch
```

##### apm.launch error
    [FATAL] [1657599759.452079697]: FCU: DeviceError:serial:open: No such file or directory
    ================================================================================REQUIRED process [mavros-2] has died!
    process has finished cleanly
    log file: /home/jaehyung/.ros/log/43aee912-019a-11ed-bc60-cd141d67ef6a/mavros-2*.log
    Initiating shutdown!
    ================================================================================
        
##### Troubleshooting
edit apm.launch which is located in ~/catkin_ws/src/mavros/mavros/launch/apm.launch
```
"<arg name="fcu_url" default="udp://127.0.0.1:14551@14555" /"
```
reference : [Ardupilot_docs](https://ardupilot.org/dev/docs/ros-sitl.html)
    
3-1) After run apm.launch, check the connection with command below
```
$ rostopic echo /mavros/state
=> connected : True
```
    
    
After 1) + 2) + 3) run, you will se like this
![image](https://user-images.githubusercontent.com/79160507/178422143-0de792f0-54cb-4856-98d2-37389c19be4b.png)

---
### Make custom node.cpp to send ROS_messages for manipulating
reference : 
    - https://docs.px4.io/main/ko/ros/mavros_offboard.html
    
1) Create Pkg [Reference:Ros_tutorials](http://wiki.ros.org/ROS/Tutorials/CreatingPackage)
```
$ catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
```
    
2) Make node.cpp
In ~/catkin_ws/src/custom_pkg/src
```
gedit your_node.cpp
```
reference : http://wiki.ros.org/mavros_msgs
위의 mavros_msg를 참고하여 사용할 msg를 node에 추가
    
3) Edit package.xml, CMakelists.txt to make dependencies for building
```
```
    
    
    

