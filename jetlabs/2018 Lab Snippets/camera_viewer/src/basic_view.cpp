#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

cv::Mat src;

image_transport::Publisher user_image_pub;
image_transport::Subscriber raw_image_sub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
	src = cv_bridge::toCvShare(msg, "rgb8")->image;
	sensor_msgs::ImagePtr image1;
	image1 = cv_bridge::CvImage(std_msgs::Header(), "rgb8", src).toImageMsg();
	user_image_pub.publish(image1);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "basic_view");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  user_image_pub = it.advertise("/user/image1", 1);
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);

  ros::spin();
}
