#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"
#define PI 3.14159265
#define l1 115
#define l2 140 //real distance
#define l3 18


int navigation_signal=1;
class ImageConverter
{
  ros::NodeHandle nh_;
  ros::Subscriber navigation_signal_;
  //image_transport::Publisher image_pub_;
  ros::Publisher choose_sub_;
  ros::Publisher pose_signal_pub_;
  ros::Publisher image_pose_move_;
  ros::Publisher robot_back;
  ros::Publisher navigation_signal_end;
  
public:
  ImageConverter()
  {
    // Subscrive to input video feed and publish output video feed
    navigation_signal_= nh_.subscribe("close_distance_move", 1, &ImageConverter::navigationCb, this);

    //navigation_signal_end = nh_.advertise<std_msgs::Int64>("navigation_signal_end",1);

  }


  void navigationCb(std_msgs::Int64 msg)
  {
	ROS_INFO("Accept");
	navigation_signal=msg.data;
	if(navigation_signal<1)
	{
        system("roslaunch kinect kinect_open.launch");
	ROS_INFO("Start");
	}
  }
 
};

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "strat_distance_move");

  ImageConverter ic;
  ros::spin();
  return 0;
}

