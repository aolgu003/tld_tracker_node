cmake_minimum_required(VERSION 2.8.3)
project(tld_tracker)
find_package(catkin REQUIRED COMPONENTS
	std_msgs
	sensor_msgs
	opencv_apps
	rostime 
	roscpp 
	rosconsole 
	roscpp_serialization 
	OpenCV 
	cv_bridge 
	image_transport
	message_generation 
  image_geometry
  tf
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
  opencv_apps
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)
add_subdirectory( include )

add_executable( tld_tracker_node src/tld_tracker_node.cpp
)

target_link_libraries( tld_tracker_node tld_tracker ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}  )
