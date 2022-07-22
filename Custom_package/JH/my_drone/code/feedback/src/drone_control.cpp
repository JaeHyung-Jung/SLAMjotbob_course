#include "drone_control/drone_control.h"

DroneControl::DroneControl()
{    
}

void DroneControl::Init()
{
    stop = false;
    set_local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);

    set_global_pos_pub = nh.advertise<geographic_msgs::GeoPoseStamped>("mavros/setpoint_position/global", 10);
    set_vel_pub = nh.advertise<geometry_msgs::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped", 10);

    get_local_pos_sub = nh.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 10, &DroneControl::PositionStateCallback, this);

    arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    takeoff_client = nh.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff");
    return;
}

void DroneControl::Run()
{
    thread = std::thread(&DroneControl::RosSpin, this);    
    return;
}

void DroneControl::Finish()
{
    stop = true;
    thread.join();
    return;
}

void DroneControl::setArm(const bool arm)
{
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = arm;
    arming_client.call(arm_cmd);

    return;
}

void DroneControl::setMode(const std::string mode)
{
    mavros_msgs::SetMode set_mode_msg;
    set_mode_msg.request.custom_mode = mode;
    set_mode_client.call(set_mode_msg);

    return;
}

void DroneControl::setTakeoff(const float alt)
{
    mavros_msgs::CommandTOL takeoff_cmd;
    takeoff_cmd.request.latitude = 0;
    takeoff_cmd.request.longitude = 0;
    takeoff_cmd.request.altitude = alt;
    takeoff_cmd.request.min_pitch = 0;
    takeoff_cmd.request.yaw = 0;
    takeoff_client.call(takeoff_cmd);

    return;
}

void DroneControl::setLocalPosePub(const float x, const float y, const float z)
{
    geometry_msgs::PoseStamped dest;
    dest.pose.position.x = x;
    dest.pose.position.y = y;
    dest.pose.position.z = z;
    set_local_pos_pub.publish(dest); 
    return;
}

void DroneControl::setVelocityPub(const float x, const float y, const float z)
{
    geometry_msgs::Twist vel;
    vel.linear.x = x;
    vel.linear.y = y;
    vel.linear.z = z;
    set_vel_pub.publish(vel);
}

std::vector<float> DroneControl::getCurrnetPosition()
{
    std::vector<float> pose;
    pose.resize(3);
    pose[0] = getpos.pose.position.x;
    pose[1] = getpos.pose.position.y;
    pose[2] = getpos.pose.position.z;
    return pose;
}
std::vector<float> DroneControl::getCurrnetOri()
{
    std::vector<float> ori;
    ori.resize(4);
    ori[0] = getpos.pose.orientation.x;
    ori[1] = getpos.pose.orientation.y;
    ori[2] = getpos.pose.orientation.z;
    ori[3] = getpos.pose.orientation.w;
    return ori;
}

void DroneControl::PositionStateCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    getpos = *msg;
}

void DroneControl::RosSpin()
{
    ros::Rate r(30);
    while(!stop)
    {
        ros::spinOnce();
        r.sleep();
    }
    return;
}