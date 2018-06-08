#include <ros/ros.h>
#include "std_msgs/UInt64.h"

int callback_ticks = 0, prev_count = 0, total_rotation = 0;

void left_encoder_callback(const std_msgs::UInt64::ConstPtr& msg){
	callback_ticks = msg->data;
}

int main(int argc, char **argv){
	while (ros::ok()){
		ROS_INFO("Forward");
		ros::Duration(5).sleep();
		total_rotation += callback_ticks;
		callback_ticks = 0;
		ros::spinOnce();
	}
}
