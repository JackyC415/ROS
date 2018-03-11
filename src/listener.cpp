	#include <ros/ros.h>
	#include <tf2_ros/transform_listener.h>
	#include <geometry_msgs/TransformStamped.h>

	/*Source code referenced tf2listener.cpp from CSE180 -- Introduction to Robotics course materials*/

	int main(int argc, char** argv){
	
	//initialize ros node
	ros::init(argc, argv, "listener");
	ros::NodeHandle nh;
	
	//publish node to topic repeatMotion
	ros::Publisher pub = nh.advertise<geometry_msgs::TransformStamped>("/repeatMotion", 1000);
	
	//initialize buffer and listener
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener listener(tfBuffer);

	//loop @ 1Hz
	ros::Rate rate(1.0);
	while (nh.ok()){
	
	geometry_msgs::TransformStamped ts;
	try{
	//obtain transformation between alpha and beta husky
	ts = tfBuffer.lookupTransform("husky_beta/base_link", "husky_alpha/base_link",ros::Time(0));
	}
	//catch exception
	catch (tf2::TransformException &ex) {
	ROS_WARN("%s",ex.what());
	ros::Duration(1.0).sleep();
	continue;
	}
	
	//display and publish transformation
	ROS_INFO_STREAM("Transformation: " << ts);
	pub.publish(ts);
	rate.sleep();
	}
	return 0;
	};
