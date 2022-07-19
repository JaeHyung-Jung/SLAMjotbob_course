#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>

#include <sstream>

#include <unistd.h>
#include <termios.h>
#include <stdio.h>

// 키입력값 설정
#define SPACEBAR 32
#define T 116
#define W 119
#define A 97
#define S 115
#define D 100
#define R 114
#define C 99
#define ENTER 10

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

// 키 입력 함수
int key_input(){
        struct termios oldattr, newattr;
        int c;

        // 1개의 키 입력 부분 (ubuntu terminal의 키입력(canonical, echo)를 끄고 키를 입력받아 변수 c에 저장)
        tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
        newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
        newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
        c = getchar();                       // 키보드 입력 읽음
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구

        return c;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "jhdrone_position");
    
    ros::NodeHandle nh;
            
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
                ("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
                ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
                ("mavros/set_mode");
    ros::ServiceClient takeoff_client = nh.serviceClient<mavros_msgs::CommandTOL>
                ("/mavros/cmd/takeoff");

    // setpoint publish rate 설정
    ros::Rate rate(20.0);   

    //// mavros 변수들 및 조작에 필요한 변수들 선언
    // mode msg parameter set
    mavros_msgs::SetMode jh_set_mode_guided;
    jh_set_mode_guided.request.custom_mode = "GUIDED";

    mavros_msgs::SetMode jh_set_mode_HOLD;
    jh_set_mode_HOLD.request.custom_mode = "POSHOLD";

    mavros_msgs::SetMode jh_set_mode_RTL;
    jh_set_mode_RTL.request.custom_mode = "RTL";

    mavros_msgs::CommandTOL tk_cmd;
    tk_cmd.request.latitude = 0;
    tk_cmd.request.longitude = 0;
    tk_cmd.request.min_pitch = 0;
    tk_cmd.request.yaw = 0;

    // arming msg parameter set
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    // 초기 시작시 키 입력문장 출력
    ROS_INFO("\nPress keys to control.\n - 'Spacebar' : Arms the robot and set mode to 'GUIDED'\n - 'T' : Take off.\n - 'W','A','S','D' : Move.\n - 'Enter' : exit.\n ");

    // ros
    while(ros::ok())
    {

    int key=key_input(), a_, x_, y_, z_;

    // spacebar키 입력의 명령 처리 : Guided모드 설정 및 arming
    if(key==SPACEBAR){
                ROS_INFO("'Spacebar'key pressed. \nSet mode to 'guided' and arm the drone.\n");
                set_mode_client.call(jh_set_mode_guided); // GUIDED
                arming_client.call(arm_cmd); // arming
    }
    
    // t키 입력 명령어 처리 : takeoff
    else if(key==T){ROS_INFO("'T'key pressed. \nEnter the height of drone.(only 1 number)\n");
                a_ = (key_input())-48; // 0=48, 1=49, ... 9=57
                ROS_INFO("Input altitude : %d\n", a_);

                // takeoff
                tk_cmd.request.altitude = a_;
                takeoff_client.call(tk_cmd); // takeoff
        }

    // w키 입력의 명령 처리 : x축 + 이동
    else if(key==W){ROS_INFO("'W'key pressed. Move forward\n");
                do{
                        x_ += 0.3;
                } while(0);
                geometry_msgs::PoseStamped pose;
                pose.pose.position.x = x_;
                pose.pose.position.y = 0;
                pose.pose.position.z = a_;
                local_pos_pub.publish(pose);
    }

    // a키 입력의 명령 처리 : y축 + 이동
    else if(key==A){ROS_INFO("'A'key pressed. Turn left\n");
                do{
                        y_ += 0.3;
                } while(0);
                geometry_msgs::PoseStamped pose;
                pose.pose.position.x = 0;
                pose.pose.position.y = y_;
                pose.pose.position.z = a_;
                local_pos_pub.publish(pose);
    }

    // s키 입력의 명령 처리 : x축 - 이동
    else if(key==S){ROS_INFO("'S'key pressed. Stop\n");
            set_mode_client.call(jh_set_mode_HOLD); // HOLD}
    }

    // d키 입력의 명령 처리 : y축 - 이동
    else if(key==D){ROS_INFO("'D'key pressed. Turn right\n");
                do{
                        y_ -= 0.3;
                } while(0);
                geometry_msgs::PoseStamped pose;
                pose.pose.position.x = 0;
                pose.pose.position.y = y_;
                pose.pose.position.z = a_;
                local_pos_pub.publish(pose);
    }

    // r키 입력의 명령 처리 : RTL
    else if(key==R){ROS_INFO("'R'key pressed. Return to Home\n");}

    // c키 입력의 명령 처리 : Rotate
    else if(key==C){ROS_INFO("'C'key pressed. Rotate\n");}

    // Enter키 입력시 종료
    else if(key==ENTER){return 0;}

    else{ROS_INFO("Other key pressed. If you want to exit, press 'Enter'key.", key);}
    ros::spinOnce();
    }
    return 0;
}
