
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

void ObjectTracker::trackObject( const sensor_msgs::ImageConstPtr& color_img  )
{
  cv::Mat lab_image;
	cv_bridge::CvImagePtr img_ptr;
  ROS_INFO("IMAGE RECEIVED");

  try 
  {
		img_ptr = cv_bridge::toCvCopy( color_img, sensor_msgs::image_encodings::BGR8 );
    image_ = img_ptr->image;
    cv::cvtColor(image_, lab_image, cv::COLOR_BGR2Lab);
    if ( !trackerInitialized_ )
    {
      //initializes the tracker
      boundingBox_ = selectROI("Tracking API", image_);

      if( !tracker_->init( lab_image, boundingBox_ ) ) 
      {
        ROS_ERROR("[TLD_TRACKER] FAILED TO INITIALIZE");
        return;
      }

      trackerInitialized_ = true;
    } 
    else 
    {
      if( tracker_->update( lab_image, boundingBox_ ) ) 
      {
        rectangle( image_, boundingBox_, cv::Scalar( 255, 0, 0 ), 2, 1 );
        object_.x_offset = boundingBox_.x;
        object_.y_offset = boundingBox_.y;
        object_.width = boundingBox_.width;
        object_.height = boundingBox_.height;
        pub_.publish(object_);
      }
    }
  } 
  catch ( cv_bridge::Exception& ex) 
  {
    ROS_ERROR("[TLD_TRACKER] Failed to convert image");
    return;
  }

  cv::imshow("Tracking API", image_);
  cv::waitKey(10);
}
