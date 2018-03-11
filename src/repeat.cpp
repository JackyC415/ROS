#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <iostream>

using namespace std;

void msgHandle(const geometry_msgs::TransformStamped&msg) {
	ROS_INFO_STREAM("Repeating Alpha Motion: ");
}

	int main(int argc, char ** argv) {

	//initialize ros node
	ros::init(argc,argv,"repeat");
	ros::NodeHandle nh;

	//subscribe to topic repeatMotion
	ros::Subscriber subTP = nh.subscribe("/repeatMotion", 1000, &msgHandle);
	//publish alpha husky movement
	ros::Publisher pubTwist = nh.advertise<geometry_msgs::Twist>("husky_alpha/husky_velocity_controller/cmd_vel",1000);

	//initialize buffer and listener
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener listener(tfBuffer);

	geometry_msgs::TransformStamped ts;
	try{
	//get initial transformation between alpha and beta husky
	ts = tfBuffer.lookupTransform("husky_beta/base_link", "husky_alpha/base_link", ros::Time(0));

	}
	//catch exception
	catch (tf2::TransformException &ex) {
	ROS_WARN("%s",ex.what());
	ros::Duration(1.0).sleep();
	}
	
	//store initial transformations into these variables for computing differences
	float initialX = ts.transform.translation.x;
	float initialY = ts.transform.translation.y;
	float initialTheta = ts.transform.rotation.z;

	//loop @ 1Hz
	ros::Rate rate(1.0);

	while(ros::ok()) {	

	try{
	//obtain current transformation between alpha and beta husky
	ts = tfBuffer.lookupTransform("husky_beta/base_link", "husky_alpha/base_link", ros::Time(0));

	}
	//catch exception
	catch (tf2::TransformException &ex) {
	ROS_WARN("%s",ex.what());
	ros::Duration(1.0).sleep();
	continue;
	}
	
	geometry_msgs::Twist pose;
	//compute the difference between current and initial transformation for each robot frames
	pose.linear.x = (ts.transform.translation.x - initialX);
	pose.linear.y = (ts.transform.translation.y - initialY);
	pose.angular.z = (ts.transform.rotation.z - initialTheta);

	//display poses to compare w/ beta husky & publish computed transformations
	ROS_INFO_STREAM("(x,y,z): " << "(" << pose.linear.x << "," << pose.linear.y << "," << pose.angular.z << ")");
	pubTwist.publish(pose);
	rate.sleep();
	ros::spinOnce(); 
	}
return 0;
};

