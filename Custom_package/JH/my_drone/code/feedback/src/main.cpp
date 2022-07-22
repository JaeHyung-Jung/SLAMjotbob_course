#include <ros/ros.h>
#include <math.h>

#include "drone_control/util.h"
#include "drone_control/drone_control.h"

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

using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "drone_control");

    DroneControl *drone_control = new DroneControl();
    drone_control->Init();
    drone_control->Run();

    bool stop = false;
    while(!stop)
    {
        int key = key_input();
        switch(key){
            case SPACEBAR:
            {
                ROS_INFO("'Spacebar'key pressed. \nSet mode to 'guided' and arm the drone.\n");
                drone_control->setMode("GUIDED");
                drone_control->setArm(true);
                break;
            }
            case T:
            {
                ROS_INFO("'T'key pressed. \nEnter the height of drone.(only 1 number)\n");
                float alt = (key_input())-48; // 0=48, 1=49, ... 9=57
                drone_control->setTakeoff(alt);
                break;
            }
            case E:
            {
                float x,y,z;
                cout << "enter position 'x' 'y' 'z' : " << endl;
                cin >> x >> y >> z;
                cout << "Input position : "<< x << "," << y << "," << z <<endl;
                drone_control->setLocalPosePub(x,y,z);
                break;
            }
            case W:
            {
                drone_control->setVelocityPub(2,0,0);
                break;
            }
            case A:
            {
                drone_control->setVelocityPub(0,2,0);
                break;
            }
            case S:
            {
                drone_control->setVelocityPub(-2,0,0);
                break;
            }
            case D:
            {
                drone_control->setVelocityPub(0,-2,0);
                break;
            }
            case Q:
            {
                drone_control->setMode("BRAKE");
                break;
            }
            case R:
            {   
                drone_control->setMode("RTL");
                break;
            }
            case ENTER:
            {
                ROS_INFO("'Enter key' pressed. \n");
                break;
            }
            case F:
            {
                drone_control->Finish();
                stop = true;
                break;
            }
            default:
                break;
        }
    }

    delete drone_control;

    return 0;

}