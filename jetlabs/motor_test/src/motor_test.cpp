#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"

void odom_callback(const nav_msgs::Odometry::ConstPtr& msg){
	ROS_INFO("Distance (m): %f", msg->pose.pose.position.x);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "motor_control");
    ros::NodeHandle nh;
    ros::Publisher vel_pub;
    ros::Subscriber odom_sub = nh.subscribe("/odom", 10, &odom_callback);
    geometry_msgs::Twist vel_msg;
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
 
    while (ros::ok()){
        ROS_INFO("Forward");
        vel_msg.linear.x = 0.5;
        vel_msg.angular.z = 0;
        vel_pub.publish(vel_msg);
        ros::Duration(2).sleep();
        
        ROS_INFO("Right Turn");
        vel_msg.linear.x = 0;
        vel_msg.angular.z = -0;
        vel_pub.publish(vel_msg);
        ros::Duration(1).sleep();
        
        ros::spinOnce();
 
        ROS_INFO("Backward");
        vel_msg.linear.x = -0.5;
        vel_msg.angular.z = 0;
        vel_pub.publish(vel_msg);
        ros::Duration(2).sleep();
 
        ROS_INFO("Left Turn");
        vel_msg.linear.x = 0;
        vel_msg.angular.z = 0;
        vel_pub.publish(vel_msg);
        ros::Duration(1).sleep();
 
        ros::spinOnce();
    }
}

