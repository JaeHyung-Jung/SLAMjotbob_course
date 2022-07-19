#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geographic_msgs/GeoPoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>

#include <sstream>

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <iostream>

using namespace std;
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
#define Q 113
#define E 101
#define F 102
#define G 103

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

geometry_msgs::PoseStamped getpos;
void position_state(const geometry_msgs::PoseStamped::ConstPtr& msg){
    getpos = *msg;
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
    ros::init(argc, argv, "jhdrone_velocity");
    
    ros::NodeHandle nh;
            
    ros::Publisher set_local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
                ("mavros/setpoint_position/local", 10);
    ros::Subscriber get_local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>
                ("mavros/local_position/pose", 10, position_state);
    ros::Publisher set_global_pos_pub = nh.advertise<geographic_msgs::GeoPoseStamped>
                ("mavros/setpoint_position/global", 10);
    ros::Publisher set_vel_pub = nh.advertise<geometry_msgs::Twist>
                ("mavros/setpoint_velocity/cmd_vel_unstamped", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
                ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
                ("mavros/set_mode");
    ros::ServiceClient takeoff_client = nh.serviceClient<mavros_msgs::CommandTOL>
                ("/mavros/cmd/takeoff");

    // setpoint publish rate 설정
    ros::Rate rate(20.0);   

    // arming msg parameter set
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    //// mavros 변수들 및 조작에 필요한 변수들 선언
    // mode msg parameter set
    mavros_msgs::SetMode jh_set_mode_guided;
    jh_set_mode_guided.request.custom_mode = "GUIDED";

    mavros_msgs::SetMode jh_set_mode_HOLD;
    jh_set_mode_HOLD.request.custom_mode = "POSHOLD";

    mavros_msgs::SetMode jh_set_mode_RTL;
    jh_set_mode_RTL.request.custom_mode = "RTL";

    mavros_msgs::SetMode jh_set_mode_BRK;
    jh_set_mode_BRK.request.custom_mode = "BRAKE";

    mavros_msgs::CommandTOL tk_cmd;
    tk_cmd.request.latitude = 0;
    tk_cmd.request.longitude = 0;
    tk_cmd.request.min_pitch = 0;
    tk_cmd.request.yaw = 0;

    // 초기 시작시 키 입력문장 출력
    ROS_INFO("\nPress keys to control.\n- 'Spacebar' : Arms the robot and set mode to 'GUIDED'\n- 'T' : Take off.\n- 'Q' : Brake.\n- 'R' : Return to Launch.\n- 'C' : Rotate.\n- 'W','A','S','D' : Move.\n- 'F' : exit.\n ");

    // ros
    while(ros::ok())
    {

    int key=key_input(), a_, x_, set_x, set_y, set_z, choice;
    float cur_x = getpos.pose.position.x, cur_y = getpos.pose.position.y, cur_z = getpos.pose.position.z;

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

    // E키 입력 명렁어 처리 : set point & move
    else if(key==E){ROS_INFO("'E'key pressed. \n Set the Poisition(x,y,z)\n");
                cout << "enter position 'x' 'y' 'z' : " << endl;
                cin >> set_x >> set_y >> set_z;
                cout << "Input position : "<< set_x << "," << set_y << "," << set_z <<endl;

                geometry_msgs::PoseStamped dest;
                dest.pose.position.x = set_x;
                dest.pose.position.y = set_y;
                dest.pose.position.z = set_z;
                set_local_pos_pub.publish(dest); // Move to setposition
    }

    // w키 입력의 명령 처리 : x축 + 이동
    else if(key==W){ROS_INFO("'W'key pressed. x_velocity +\n");
                
                geometry_msgs::Twist vel;
                vel.linear.x = 2;
                vel.linear.y = 0;
                vel.linear.z = 0;
                set_vel_pub.publish(vel);
    }

    // a키 입력의 명령 처리 : y축 + 이동
    else if(key==A){ROS_INFO("'A'key pressed. y_velocity +\n");
                geometry_msgs::Twist vel;
                vel.linear.x = 0;
                vel.linear.y = 2;
                vel.linear.z = 0;
                set_vel_pub.publish(vel);
    }

    // s키 입력의 명령 처리 : x축 - 이동
    else if(key==S){ROS_INFO("'S'key pressed. x_velocity -\n");
                geometry_msgs::Twist vel;
                vel.linear.x = -2;
                vel.linear.y = 0;
                vel.linear.z = 0;
                set_vel_pub.publish(vel);
    }

    // d키 입력의 명령 처리 : y축 - 이동
    else if(key==D){ROS_INFO("'D'key pressed. y_velocity -\n");
                geometry_msgs::Twist vel;
                vel.linear.x = 0;
                vel.linear.y = -2;
                vel.linear.z = 0;
                set_vel_pub.publish(vel);
    }
 
    // q키 입력의 명령 처리 : 정지
    else if(key==Q){ROS_INFO("'Q'key pressed. Set mode Brake\n");
                set_mode_client.call(jh_set_mode_BRK); // Brake
    }

    // r키 입력의 명령 처리 : RTL (RTL말고 setpoint.position (0,0,0)으로도 가능)
    else if(key==R){ROS_INFO("'R'key pressed. Return to launch\n");
                set_mode_client.call(jh_set_mode_RTL); // RTL
    }

    // c키 입력의 명령 처리 : Rotate (현재 position x,y,z를 받고 position기반 원회전 (머리는 position을보게))
    else if(key==C){ROS_INFO("'C'key pressed. Rotate \n");
                cout<<"1: Rotate using position \n"<<endl;
                cout<<"2: Rotate using velocity \n"<<endl;
                cout<<"3: Rotate using altitude \n"<<endl;
                cout<<"원하는 기능의 숫자를 입력하시오. : \n";
                cin >> choice;

                ros::Duration duration(5);
                //ROS_INFO("Rotate center(x,y,z) : %4.2f, %4.2f, %4.2f", cur_x, cur_y, cur_z);
                /*
                geometry_msgs::PoseStamped pos1;
                pos1.pose.position.x = cur_x;
                pos1.pose.position.y = cur_y - 5;
                pos1.pose.position.z = cur_z;

                geometry_msgs::PoseStamped pos2;
                pos2.pose.position.x = cur_x + 5;
                pos2.pose.position.y = cur_y;
                pos2.pose.position.z = cur_z;
                pos2.pose.orientation.z = 10;
                pos2.pose.orientation.w = 90;

                geometry_msgs::PoseStamped pos3;
                pos3.pose.position.x = cur_x;
                pos3.pose.position.y = cur_y + 5;
                pos3.pose.position.z = cur_z;

                geometry_msgs::PoseStamped pos4;
                pos4.pose.position.x = cur_x - 5;
                pos4.pose.position.y = cur_y;
                pos4.pose.position.z = cur_z;

                geometry_msgs::PoseStamped pos_origin;
                pos_origin.pose.position.x = cur_x;
                pos_origin.pose.position.y = cur_y;
                pos_origin.pose.position.z = cur_z;
                */
                switch(choice)
                {
                    case 1 :
                        cout << "Rotate using position" << endl;
                        set_local_pos_pub.publish(pos1);
                        duration.sleep();
                        set_local_pos_pub.publish(pos2);
                        duration.sleep();
                        set_local_pos_pub.publish(pos3);
                        duration.sleep();
                        set_local_pos_pub.publish(pos4);
                        duration.sleep();
                        set_local_pos_pub.publish(pos1);
                        duration.sleep();
                        set_local_pos_pub.publish(pos_origin);
                        duration.sleep();
                        cout << "Rotate finished. \n";
                        break;
                    case 2 :
                        cout << "Rotate using velocity" << endl;
                        break;
                    case 3 : 
                        cout << "Rotate using attitude" << endl;
                        break;
                    case ENTER :
                        cout << " ";
                        break;
                    default : 
                        cout << "잘못된 입력입니다. \n" << endl;
                }
                //ROS_INFO("Current Position(x,y,z) : %4.2f, %4.2f, %4.2f", cur_x, cur_y, cur_z);
    }

    else if(key==G){ROS_INFO("'G'key pressed. Get current Position (x,y,z) \n");
                ROS_INFO("Current Position(x,y,z) : %4.2f, %4.2f, %4.2f", cur_x, cur_y, cur_z);
    }


    // Setpoint의 cin을 위한 enter키 문구
    else if(key==ENTER) {ROS_INFO("'Enter key' pressed. \n");}

    // F키 입력시 종료
    else if(key==F){return 0;}

    else{ROS_INFO("Other key pressed. If you want to exit, press 'Enter'key.", key);}
    ros::spinOnce();
    }
    return 0;
}
