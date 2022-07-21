# SLAMjotbob_course

### Repository 설명
```
Xavier setting, Custom pkg create, SLAM analyzation & implementation course과정을 정리한 Repository 
    - 참여자 : 정재형, 이 담
    - 주 관 : 신성균
    - Assist : 이민재, 조우성
```
## Course schedules

### * Xavier Setting (~7.11)
- [x] 1) SDK Manager를 통해 Xavier 설치
- [x] 2) ROS Noetic 설치 on Xavier
- [x] 3) Mavros 설치 on Xavier
- [x] 4) Pixhawk와 Xavier연결
- [x] 5) roslaunch 자동실행
- [x] 6) USB devide 고정 (dev ID 입력, symbolic link 생성, 권한부여)
- [x] 7) Opencv install & build
- [x] 8) Lidar & IMU 연결 및 설치 (ref : velodyne ros wiki)

### * Drone schedule(JH, LD ~ 10.1)	
- [x] (~7.11) Xavier Setting
- [X] (7.11~7.21) ROS custom package create(input image.cpp, manipulation.cpp)
- basic function<br>
    spacebar : arming (propeller <br>
    t : takeoff // height select <br>
    e : set local postition (move) => guided mode <br>
    c : rotate <br>
    r : take off 위치로 return(rtl)<br>

- additional function<br><br>
    Q : Brake <br>
    W,A,S,D : Move control<br>
    F : Exit<br>
    G : Get current position<br>

- [ ] (7.21 ~ 7.29) Simulation env Setting 
    - Xavier : Rospkg, Mavros, Ardupilot, Opencv
    - TF : URDF(depth, stereo, lidar, IMU, gps) + camera module
    - Joint Link + Joint state publisher
    - map + baseLink ?? 이거뭐임
    - Lidar 처음부터 구성
    
- [ ] (7.29 ~ 10.1) 
    - ROS pkg custom create(.cpp)
    - SLAM(Lom, Lego, Vision, Lidar, ...) 논문 및 코드 분석
    - Drone simulator + SLAM 

---
### <div align="center"> Simulation concept </div>
![image](https://user-images.githubusercontent.com/79160507/178926870-19e59e3f-d8c6-47a6-842d-4ec2847d4a92.png)
