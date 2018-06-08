#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <dynamic_reconfigure/server.h>
#include "camera_viewer/hsvConfig.h"

using namespace cv;

Mat src, hsv, gray, res;
int h_lower, s_lower, v_lower, h_upper, s_upper, v_upper;
Moments moi;
Point center_of_mass;

image_transport::Publisher user_image_pub;
image_transport::Publisher user_image_pub2;
image_transport::Subscriber raw_image_sub;

void reconfigureCallback(camera_viewer::hsvConfig &config, uint32_t level){
	h_upper = config.h_upper;
	h_lower = config.h_lower;
	s_upper = config.s_upper;
	s_lower = config.s_lower;
	v_upper = config.v_upper;
	v_lower = config.v_lower;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
	src = cv_bridge::toCvShare(msg, "rgb8")->image;
	cvtColor(src, hsv, CV_RGB2HSV);
	Scalar lower_boundary(h_lower, s_lower, v_lower);
	Scalar upper_boundary(h_upper, s_upper, v_upper);
	inRange(hsv, lower_boundary, upper_boundary, gray);
	cvtColor(gray, res, CV_GRAY2RGB);
	bitwise_and(src, res, res, gray);
	moi = moments(gray, true);
	center_of_mass.x = moi.m10 / moi.m00;
	center_of_mass.y = moi.m01 / moi.m00;
	circle(res, center_of_mass, 5, Scalar(255,0,0), -1);
	sensor_msgs::ImagePtr image1, image2;
	image1 = cv_bridge::CvImage(std_msgs::Header(), "mono8", gray).toImageMsg();
	image2 = cv_bridge::CvImage(std_msgs::Header(), "rgb8", res).toImageMsg();
	user_image_pub.publish(image1);
	user_image_pub2.publish(image2);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "color_isolation");
  ros::NodeHandle nh;
 
  dynamic_reconfigure::Server<camera_viewer::hsvConfig> config_server;
  dynamic_reconfigure::Server<camera_viewer::hsvConfig>::CallbackType f;
  f = boost::bind(&reconfigureCallback, _1, _2);
  config_server.setCallback(f);

  image_transport::ImageTransport it(nh);

  user_image_pub = it.advertise("/user/image1", 1);
  user_image_pub2 = it.advertise("/user/image2", 1);
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);
 
  ros::spin();
}
