#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

cv::Mat src, gray, cdst;

image_transport::Publisher user_image_pub;
image_transport::Subscriber raw_image_sub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
	src = cv_bridge::toCvShare(msg, "rgb8")->image;
	cvtColor(src, gray, CV_RGB2GRAY);
	cvtColor(gray, cdst, CV_GRAY2RGB);
	sensor_msgs::ImagePtr image1;
	image1 = cv_bridge::CvImage(std_msgs::Header(), "mono8", gray).toImageMsg();
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
