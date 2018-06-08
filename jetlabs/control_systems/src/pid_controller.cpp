#include <ros/ros.h>
#include "std_msgs/Int16.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>

using namespace std;

double ref = 20.0, error, dist;
double speed, Kp = 0.100;

void sonar2_callback(const std_msgs::Int16::ConstPtr& msg){
	dist = msg->data;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "sonar_sensor_example");
	ros::NodeHandle nh;
	std_msgs::Int16 msg;
	geometry_msgs::Twist input;
	
	nh.param<double>("Kp", Kp, 0.0);
	//nh.param<double>("Ki", Ki, 0.0);
	//nh.param<double>("Kd", Kd, 0.0);
	
	ros::Publisher input_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Subscriber sonar_sub = nh.subscribe("/arduino/sonar_2", 10, &sonar2_callback);
	
	while (ros::ok()){
		error = dist - ref;
		speed = Kp * error;
		cout << speed << endl;
		//input.linear.x = speed;
		//input_pub.publish(input);
		ros::Duration(0.05).sleep();
		ros::spinOnce();
	}
}
