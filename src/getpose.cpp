#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

ros::init(argc, argv, "husky_gotopose");

ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<geometry_msgs::Pose2D>("targetpose", 1000);

geometry_msgs::Pose2D pose;

while(ros::ok()) {

//reads in (x,y,theta)
cout << "Enter x-position: ";
cin >> pose.x;
cout << "Enter y-position: ";
cin >> pose.y;
cout << "Enter theta: ";
cin >> pose.theta;

pub.publish(pose);
}
return 0;
}
