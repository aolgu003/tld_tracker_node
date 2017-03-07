#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <image_geometry/pinhole_camera_model.h>

#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/RegionOfInterest.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <sensor_msgs/Image.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include "tld_tracker.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tld_tracker");

  ROS_INFO( "Initialized");
  cv::namedWindow( "Tracking API");
  ObjectTracker tld_tracker;

  ros::Time begin = ros::Time::now();
  ros::Rate loop_rate(10);
  
  double prevTick = 0;
  double ticks = 0;
  double dt = 0;

  while ( ros::ok() ) {
    ros::spinOnce();
    loop_rate.sleep();
  }
}
