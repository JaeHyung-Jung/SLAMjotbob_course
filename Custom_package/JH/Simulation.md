### <div align=center> Simulation concept drawing <div>
![image](https://user-images.githubusercontent.com/79160507/178412154-a51bd9bc-619f-41e0-a44e-d2bc7f991e0c.png)

---

### Simulation Sequence

1) Run gazebo
```
~$ gazebo --verbose ~/ardupilot_gazebo/worlds/iris_arducopter_runway.world
```

2) Run ardupilot
```
~/ardupilot/Arducopter $ ../Tools/autotest/sim_vehicle.py -f gazebo-iris --console --map
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
"<arg name="fcu_url" default="udp://:11311@" />"
```
  
4)
