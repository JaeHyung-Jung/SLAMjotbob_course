# SLAMjotbob_course

```
Xavier setting, Custom pkg create, simulation setting, SLAM analyzation & implementation course
    - 참여자 : 정재형, 이 담
    - 주 관 : 신성균
    - Assist : 이민재, 조우성
```
### Course schedule(JH, LD ~ 10.1)	
- [x] (~7.11) Xavier Setting
    - SDK Manager를 통해 Xavier 설치
    - ROS Noetic 설치 on Xavier
    - Mavros 설치 on Xavier
    - Pixhawk와 Xavier연결
    - roslaunch 자동실행
    - USB devide 고정 (dev ID 입력, symbolic link 생성, 권한부여)
    - Opencv install & build
    - Lidar & IMU 연결 및 설치 (ref : velodyne ros wiki)

- [X] (7.11~7.21) ROS custom package create(input image.cpp, manipulation.cpp)
    - basic function<br>
        Spacebar : arming, set mode to 'GUIDED' <br>
        T : takeoff // height select <br>
        E : set local postition (move) => guided mode <br>
        C : rotate <br>
        R : take off 위치로 return(rtl)<br>
    - additional function<br>
        Q : brake <br>
        W,A,S,D : move control<br>
        F : exit<br>
        G : get current position<br>
- [ ] (7.21 ~ 7.29) Simulation env Setting URDF(+TF, +Plugin)
    - Velodyne Lidar 
    - Depth Camera
    - Mono Camera
    - IMU
    - Gazebo drone model (typhoon)
    - World map   
    
- [ ] (7.29 ~ 10.1) 
        - ROS pkg custom create(.cpp)
        - SLAM(Lom, Lego, Vision, Lidar, ...) 논문 및 코드 분석
        - Drone simulator + SLAM 

---
### <div align="center"> Simulation concept </div>
![image](https://user-images.githubusercontent.com/79160507/178926870-19e59e3f-d8c6-47a6-842d-4ec2847d4a92.png)
