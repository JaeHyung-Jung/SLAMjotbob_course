// ros, mavros header
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

// c++ header
#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
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
#define PI 3.1415952

// mavros msg
mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

// geometry msg for getting current position 
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

// main
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

    // 초기 시작시 키 입력문장 출력
    ROS_INFO("\nPress keys to control.\n- 'Spacebar' : Arms the robot and set mode to 'GUIDED'\n- 'Q' : Brake.\n- 'W','A','S','D' : Move.\n- 'E' : Set position to go.\n- 'R' : Return to Launch.\n- 'T' : Take off.\n- 'G' : Get current position.\n- 'C' : Rotate.\n- 'F' : exit.\n ");

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

    // rotate using vel test
    geometry_msgs::Twist vel1;
    vel1.angular.x = 0;
    vel1.angular.y = 0;
    vel1.angular.z = 0.5;
    // rotate using vel test

    geometry_msgs::PoseStamped rot;
    
    // ros
    while(ros::ok())
    {

    // 변수 선언
    int key = key_input(), radian, choice, a_, set_x, set_y, set_z;
    float cur_x = getpos.pose.position.x, cur_y = getpos.pose.position.y, cur_z = getpos.pose.position.z;
    float cur_ox = getpos.pose.orientation.x, cur_oy = getpos.pose.orientation.y, cur_oz = getpos.pose.orientation.z, cur_w = getpos.pose.orientation.w;
    // spacebar키 입력의 명령 처리 : Guided모드 설정 및 arming

    geometry_msgs::PoseStamped pos1;
    pos1.pose.position.x = cur_x;
    pos1.pose.position.y = cur_y - 5;
    pos1.pose.position.z = cur_z;
    pos1.pose.orientation.z = 0.7071068;
    pos1.pose.orientation.w = 0.7071068;

    geometry_msgs::PoseStamped pos2;
    pos2.pose.position.x = cur_x + 3.53;
    pos2.pose.position.y = cur_y - 3.53;
    pos2.pose.position.z = cur_z;
    pos2.pose.orientation.z = 0.9238795;
    pos2.pose.orientation.w = 0.3826834;

    geometry_msgs::PoseStamped pos3;
    pos3.pose.position.x = cur_x +5;
    pos3.pose.position.y = cur_y;
    pos3.pose.position.z = cur_z;
    pos3.pose.orientation.z = 1;
    pos3.pose.orientation.w = 0;

    geometry_msgs::PoseStamped pos4;
    pos4.pose.position.x = cur_x +3.53;
    pos4.pose.position.y = cur_y + 3.53;
    pos4.pose.position.z = cur_z;
    pos4.pose.orientation.z = 0.9238795;
    pos4.pose.orientation.w = -0.3826834;

    geometry_msgs::PoseStamped pos5;
    pos5.pose.position.x = cur_x;
    pos5.pose.position.y = cur_y+5;
    pos5.pose.position.z = cur_z;
    pos5.pose.orientation.z = 0.7071068;
    pos5.pose.orientation.w = -0.7071068;

    geometry_msgs::PoseStamped pos6;
    pos6.pose.position.x = cur_x - 3.53;
    pos6.pose.position.y = cur_y + 3.53;
    pos6.pose.position.z = cur_z;
    pos6.pose.orientation.z = 0.3826834;
    pos6.pose.orientation.w = -0.9238795;

    geometry_msgs::PoseStamped pos7;
    pos7.pose.position.x = cur_x - 5;
    pos7.pose.position.y = cur_y;
    pos7.pose.position.z = cur_z;
    pos7.pose.orientation.z = 0;
    pos7.pose.orientation.w = -1;

    geometry_msgs::PoseStamped pos8;
    pos8.pose.position.x = cur_x - 3.53;
    pos8.pose.position.y = cur_y - 3.53;
    pos8.pose.position.z = cur_z;
    pos8.pose.orientation.z = 0.3826834;
    pos8.pose.orientation.w = 0.9238795;
    
    /*
    geometry_msgs::PoseStamped pos1_ori;
    pos1_ori.pose.position.x = cur_x;
    pos1_ori.pose.position.y = cur_y - 5;
    pos1_ori.pose.position.z = cur_z;
    pos1_ori.pose.orientation.z = 0.125;
    pos1_ori.pose.orientation.w = -1;
    */

    geometry_msgs::PoseStamped pos_origin;
    pos_origin.pose.position.x = cur_x;
    pos_origin.pose.position.y = cur_y;
    pos_origin.pose.position.z = cur_z;
    //// rotate using position(8)

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
                cout<<"1: Rotate using radian position \n"<<endl;
                cout<<"2: Rotate using 8 position \n"<<endl;
                cout<<"3: Rotate using velocity \n"<<endl;
                cout<<"4: Rotate using attitude \n"<<endl;
                cout<<"원하는 기능의 숫자를 입력하시오. : \n";
                cin >> choice;

                ros::Duration duration(1.6);
                ros::Duration rot_duration(0.05);
                ros::Duration last_duration(0.5);
                ros::Rate rate(20.0);

                switch(choice)
                {
                    case 1 :
                    {
                        cout << "Rotate using radian position"<< endl;
                        for(int degree=1; degree <= 360 ; degree++){
                          
                            radian=degree*PI/180;
                            int orient_radian = (degree+180)*PI/180;
                            rot.pose.position.x=((cos(radian))*10) + cur_x;
                            rot.pose.position.y=((sin(radian))*10) + cur_y;
                            rot.pose.position.z=cur_z;
                            rot.pose.orientation.z=sin(orient_radian/2);
                            rot.pose.orientation.w=cos(orient_radian/2);
                            set_local_pos_pub.publish(rot);
                            ros::spinOnce();      
                            rot_duration.sleep();
                            if(degree==360){
                                last_duration.sleep();
                                set_local_pos_pub.publish(pos_origin);
                                break;
                            }
                        }      
                        break;
                    }

                    case 2 :
                        cout << "Rotate using 8 position" << endl;
                        
                        set_local_pos_pub.publish(pos1);
                        duration.sleep();
                        set_local_pos_pub.publish(pos2);
                        duration.sleep();
                        set_local_pos_pub.publish(pos3);
                        duration.sleep();
                        set_local_pos_pub.publish(pos4);
                        duration.sleep();
                        set_local_pos_pub.publish(pos5);
                        duration.sleep();
                        set_local_pos_pub.publish(pos6);
                        duration.sleep();
                        set_local_pos_pub.publish(pos7);
                        duration.sleep();
                        set_local_pos_pub.publish(pos8);
                        duration.sleep();
                        set_local_pos_pub.publish(pos1);
                        duration.sleep();
                        set_local_pos_pub.publish(pos_origin);
                        duration.sleep();
                        cout << "Rotate finished. \n";
                        break;
                        
                    case 3 :
                    {
                        cout << "Not yet implemented" << endl;
                        break;
                    }

                    case 4 : 
                        cout << "Not yet implemented" << endl;
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
                ROS_INFO("Current Angle(x,y,z,w) : %4.2f, %4.2f, %4.2f, %4.2f", cur_ox, cur_oy, cur_oz, cur_w);
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
