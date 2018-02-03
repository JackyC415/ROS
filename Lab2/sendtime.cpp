#include <ros/ros.h>
#include <std_msgs/Time.h>

void msgHandle(const std_msgs::Time&msg) {
ROS_INFO_STREAM("Sending time " << msg.data);
}

int main(int argc, char ** argv) {

ros::init(argc,argv, "sendtime");
ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<std_msgs::Time>("timetopic", 1000, &msgHandle);

ros::Rate rate(1);
std_msgs::Time timeToSend;

while(ros::ok()) {

timeToSend.data = ros::Time::now();
pub.publish(timeToSend);
rate.sleep();
}
}
