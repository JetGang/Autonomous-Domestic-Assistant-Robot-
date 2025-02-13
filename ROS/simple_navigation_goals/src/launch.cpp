#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"
#define PI 3.14159265
#define l1 115
#define l2 140 //real distance
#define l3 18


int navigation_signal=0;
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
    navigation_signal_= nh_.subscribe("navigation_signal_end", 1, &ImageConverter::navigationCb, this);

    navigation_signal_end = nh_.advertise<std_msgs::Int64>("navigation_signal_end",1);

  }


  void navigationCb(std_msgs::Int64 msg)
  {
	ROS_INFO("Accept");
	navigation_signal=msg.data;
        int a=0;
	if(navigation_signal>0)
	{
	ROS_INFO("Start");
	system("roslaunch simple_navigation_goals 12.launch");
	a=1;
	}
	if(navigation_signal<0.1&&a>0)
	{
        system("rosnode kill web_video_server");
	ROS_INFO("Stop");
	a=0;
	}
  }
 
};

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "listener");

  ImageConverter ic;
  ros::spin();
  return 0;
}

