#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include <sstream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "jhtalker");

    ros::NodeHandle nh;

    ros::Publisher drone_pub = nh.advertise<std_msgs::String>("custom_chatter",1000);

    ros::Rate loop_rate(0.1);

    int count = 0;
    while (ros::ok())
    {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "my_drone_takeoff" << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());
        
        drone_pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}
