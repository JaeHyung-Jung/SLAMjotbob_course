```
// SET LOCAL POSITION with velocity
#define _CRT_NONSTDC_NO_WARNINGS
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
// 수학 헤더파일
#include <math.h> // 수학함수를 가지고 있는 헤더파일

#define PI 3.1415952

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h> //기준 좌표계와 타임스탬프가 있는 Pose
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <mavros_msgs/CommandBool.h> //servies - switch command의 종류로 cmd/arming 아밍 상태 바꿈
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h> //services - FCU모드 설정
#include <mavros_msgs/State.h> // sevices-아밍 사건 소스 / pub-fcu 상태

#define t 116
#define f 102

mavros_msgs::State current_state; 
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

int getch(){ // linux에서 키보드 입력 쓰는 방법
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
    c = getchar();                               // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
    return c;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dam_set_circle");
    ros::NodeHandle nh;
 
    int text = getch();
    double radian=0.0;

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);

    ros::Rate rate(20.0);
    
    geometry_msgs::PoseStamped dam_set_circle_cmd;
    
    ros::Duration duration(0.2);

    if(text==t) {
        for(int i = 100; ros::ok() && i > 0; --i){
            for(int degree=1;degree <=360;degree++){
                radian=degree*PI/180;
                dam_set_circle_cmd.pose.position.x=(cos(radian))*2;
                dam_set_circle_cmd.pose.position.y=(sin(radian))*2;
                dam_set_circle_cmd.pose.position.z=10;
                dam_set_circle_cmd.pose.orientation.z=1;
                local_pos_pub.publish(dam_set_circle_cmd);
                //duration.sleep();
                ros::spinOnce();
                rate.sleep();   
        }
        }
    }

    else if(text==f)
    {
        std::cout <<"Exit program. \n";
        return 0;
    }
    ros::Time last_request = ros::Time::now();

	ros::spinOnce();
	rate.sleep();

    return 0;
}

```
