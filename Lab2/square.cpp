#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

int main(int argc, char** argv) {

ros::init(argc, argv, "husky_movement_square");
//initalize node
ros::NodeHandle nh;
//publish the node based on geometry_msgs::Twist w/ "cmd_vel" topic
ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel", 1000);
//loop @ rate of 10Hz
ros::Rate rate(10);
geometry_msgs::Twist move;

//while true... perform the following
while(ros::ok()) {

for(int i = 0; i < 40; i++) {
//move forward w/ x-frame @ 5m/s
move.linear.x = 5;
//no movement w/ z-frame
move.angular.z = 0;
//publish the msg
pub.publish(move);
//stop temporarily
rate.sleep();
}

for(int j = 0; j < 8; j++) {
//stop moving forward
move.linear.x = 0;
//turn with pi/2 rad/s
move.angular.z = M_PI/2;
//publish the msg
pub.publish(move);
//stop temporarily again
rate.sleep();
}

}
}
