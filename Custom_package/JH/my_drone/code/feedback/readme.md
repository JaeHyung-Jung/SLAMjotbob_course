#### my_drone 패키지의 jhdrone.cpp 소스코드를 CTO(신성균이사)님이 수정, 보완한 소스코드의 분석 

### 패키지 구조

```
- drone_control
    - include
        - drone_control
            drone_control.h
            util.h
    - src
        drone_control.cpp
        main.cpp
    CMakelists.txt
    package.xml
```

#### 분석
- drone_control.h : DroneControl이라는 Class를 선언하고 그 Class안에 setArm, setMode, setTakeoff, setLocalPosePub, setVelocityPub msgs, 및 기타 변수들이 선언돼있다. DroneControl의 생성자는 존재하지만 파괴자는 존재하지않는다. 기존의 코드에서는 종료를 'return 0;'를 통해서 처리했지만 RosSpin()함수에 stop이라는 변수를 통해 종료처리를 한다.

- util.h : 키 입력을 위한 함수인 key_input()의 자료형, 이름, 기능이 구현돼있다.

- drone_control.cpp : DroneControl.h를 include하고 클래스를 불러온다. DroneControl Class에 선언된 함수(Init, Run, Finish, setArm, ...)의 기능이 담긴 코드가 있다.

- main.cpp : 두가지 header file(drone_control.h, util.h)을 include한다.
키 입력을 위한 key와 integer의 define이 돼있고 DroneControl 클래스를 사용하기 위해 클래스 변수를 포인터로 지정한다. (DroneControl *drone_control = new DroneControl();)
main에서는 switch, case문을 통해 각각의 키입력의 구현을 분리했고 case문 안 함수를 실행시켜 Drone_Control class의 함수를 callback하여 기능을 수행한다.

- CMakelists.txt :
find_package, catkin_package, include_directories, set(dir 지정), add_library, add_dependencies, add_executable, target_link_libraries, target_link_libraries 

- Package.xml : 기본적인 구조와 거의 동일하다. 'roscpp', 'rospy', 'std_msgs', 'geometry_msgs', 'mavros_msgs'가 exec, build_export, build_depend 의존성에 포함된다. buildtooL_expend 의존성은 'catkin'을 포함한다.
