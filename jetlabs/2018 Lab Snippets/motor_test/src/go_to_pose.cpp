#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "stdio.h"
#include "math.h"

#define PI 3.141592

const double timestep = 0.005;
double x_pos = 0, y_pos = 0, z_rot = 0;
geometry_msgs::Twist msg;
ros::Publisher pose_pub;

void face_angle(double angle, double speed, ros::Publisher pub){
	//Define local vars
	double time = 0;
	double timer;
	//Calculate total operation time
	timer = angle / speed;
	//Set up message
	msg.linear.x = 0;
	msg.angular.z = speed * PI / 180;
	//Loop to enforce operation time
	while (time < timer){
		//Update rotation
		z_rot += ((speed * PI / 180) * timestep);
		//Update timer
		time += timestep;
		//Publish message and wait
		pub.publish(msg);
		std::cout << time << std::endl;
		ros::Duration(timestep).sleep();
	}
	//Stop operation
	msg.angular.z = 0;
	pub.publish(msg);
}

void drive_straight(double distance, double speed, ros::Publisher pub){
	double time = 0;
	double timer;
	timer = distance / speed;
	msg.angular.z = 0;
	msg.linear.x = speed;
	
	while (time < timer){
		x_pos += ((cos(z_rot) * distance) * timestep);
		y_pos += ((sin(z_rot) * distance) * timestep);
		time += timestep;
		pub.publish(msg);
		std::cout << time << std::endl;
		ros::Duration(timestep).sleep();
	}
	msg.linear.x = 0;
	pub.publish(msg);
}

void go_to_position(double x, double y, double speed, ros::Publisher pub){
	double time = 0;
	double timer, angle, distance;
	//Determine straight-line distance
	distance = sqrt(pow(x - x_pos, 2) + pow(y - y_pos, 2));
	//Determine angle from current angle
	angle = atan2((y - y_pos), (x - x_pos)) - z_rot;
	face_angle(angle, angle, pub);  //One second turn time
	drive_straight(distance, speed, pub);
	pub.publish(msg);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "go_to_pose");
	ros::NodeHandle nh;
	
	pose_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Duration(3).sleep();
	std::cout << "Hello" << std::endl;
	face_angle(180, 135, pose_pub);
	ros::Duration(1).sleep();
	drive_straight(2, 1, pose_pub);
}
