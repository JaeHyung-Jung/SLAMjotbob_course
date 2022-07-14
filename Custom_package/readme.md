# Custom_ROS_Package

## Description :
    - (7.11~7.22) ROS custom package create(input image.cpp, manipulation.cpp)
            a : arming (propeller 
            s : takeoff // height select
            d : set local postition (move) => guided mode
            r : take off 위치로 return(rtl)
                        x : 원비행(제자리회전X)
                        setpoint : 특정 x,y,z입력하면 그곳으로 가게
            
            subscirbe, publisher

## Required :
- ROS
- Mavros(+Mavlink)
- Gazebo    
- Ardupilot(+Ardupilot_gazebo plugin)
    

