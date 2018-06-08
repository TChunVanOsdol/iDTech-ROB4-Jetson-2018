#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
const float timestep = 0.25;

float gyroZ;

void gyro_callback(const geometry_msgs::Twist::ConstPtr& gyro){
	gyroZ = gyro->angular.z;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "gyro_lab");
	ros::NodeHandle nh;
	ros::Subscriber gyro_sub = nh.subscribe("arduino/gyro", 1000, gyro_callback);
	while (ros::ok()){
		ROS_INFO("%f", gyroZ);
		ros::Duration(timestep).sleep();
		ros::spinOnce();
	}
	
	return 0;
}
