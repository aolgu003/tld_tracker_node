#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <image_geometry/pinhole_camera_model.h>
#include <tf/transform_listener.h>

#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/RegionOfInterest.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <sensor_msgs/Image.h>
#include <opencv/cv.h>
#include <opencv/cv.hpp>


#include <opencv/cv.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


class ObjectTracker 
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber sub_;
  ros::Publisher pub_;

  tf::TransformListener tf_listener_;
  image_geometry::PinholeCameraModel cam_model_;
  std::vector<std::string> frame_ids_;

  cv::Ptr<cv::Tracker> tracker_ = cv::Tracker::create( "TLD" );

  cv::KalmanFilter kf_;
  cv::Mat state_;
  cv::Mat meas_;
  cv::Mat procNoise_;

  cv::Mat image_;
  cv::Mat templateImage_;
  cv::Rect2d boundingBox_;
  cv::Rect2d predictedBoundingBox_;
	sensor_msgs::RegionOfInterest object_;

  bool paused_;
  bool selectObject_;
  bool startSelection_;
  bool objectSelected_;
  bool trackerInitialized_;
  bool firstTrack_;

  int stateSize_;
  int measSize_;
  int contrSize_;
  unsigned int type_;

  public:
    ObjectTracker()
      : it_(nh_), 
        selectObject_(false), 
        startSelection_(false), 
        objectSelected_(false),
        stateSize_(6),
        measSize_(4),
        contrSize_(0),
        type_(CV_32F)
    {

      ROS_INFO( "ENTERING CONSTRUCTOR");
      sub_ = it_.subscribe( "cv_camera/image_raw", 1, &ObjectTracker::trackObject, this );
	    pub_ = nh_.advertise<sensor_msgs::RegionOfInterest>("/object_Tracker/roi", 10);
      ROS_INFO( "Subbed" );
    }

    ~ObjectTracker() {
      cv::destroyWindow("Tracking API");
    }

    void trackObject( const sensor_msgs::ImageConstPtr& color_img );
};

