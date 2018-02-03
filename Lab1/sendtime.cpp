#include <ros/ros.h>
#include <std_msgs/Time.h>

int main(int argc, char ** argv) {

ros::init(argc,argv,"sendtime");
ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<std_msgs::Time>("timetopic",1000);

ros::Rate rate(1);
std_msgs::Time timeToSend;

while(ros::ok()) {

timeToSend.data = ros::Time::now();
pub.publish(timeToSend);
rate.sleep();
}
}
