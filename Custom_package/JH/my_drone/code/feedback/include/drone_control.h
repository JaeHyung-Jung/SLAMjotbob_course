#ifndef DRONE_CONTROL_H
#define DRONE_CONTROL_H

#include <ros/ros.h>

#include <std_msgs/String.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geographic_msgs/GeoPoseStamped.h>
#include <thread>

class DroneControl
{

    public:
        DroneControl();
        void Init();
        void Run();
        void Finish();

        void setArm(const bool arm);
        void setMode(const std::string mode);
        void setTakeoff(const float alt);
        void setLocalPosePub(const float x, const float y, const float z);    
        void setVelocityPub(const float x, const float y, const float z);

        std::vector<float> getCurrnetPosition();
        std::vector<float> getCurrnetOri();


    private:

        void RosSpin();

        void PositionStateCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);

        std::thread thread;

        ros::NodeHandle nh;

        ros::Publisher set_local_pos_pub;
        ros::Publisher set_global_pos_pub;
        ros::Publisher set_vel_pub;

        ros::Subscriber get_local_pos_sub;

        ros::ServiceClient arming_client;
        ros::ServiceClient set_mode_client;
        ros::ServiceClient takeoff_client;


        geometry_msgs::PoseStamped getpos;

        bool stop;

};

#endif