#include <ros/ros.h>
#include <std_msgs/Time.h>

void msgHandle(const std_msgs::Time&msg) {
ROS_INFO_STREAM("Received time " << msg.data);
}

int main(int argc, char ** argv) {

ros::init(argc,argv,"Receiver");
ros::NodeHandle nh;

ros::Subscriber sub = nh.subscribe("timetopic", 1000, &msgHandle);

ros::spin();
}
