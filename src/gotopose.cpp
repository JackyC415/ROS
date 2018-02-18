#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Twist.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <cmath>
#include <iostream>

using namespace std;

/*Referenced tflistener.cpp from CSE180 course materials for guidance*/

//frame global variables initalization
float x, y, theta;

//function to handle user input for frames
void pose2DMsg(const geometry_msgs::Pose2D&msg) {
     
    x = msg.x;
    y = msg.y;
    theta = msg.theta;
}

int main(int argc, char ** argv) {

//initialize ros & node
ros::init(argc,argv,"gotopose");
ros::NodeHandle nh;

//gotopose is both subscriber and publisher; sub to targetpose pub to velocity
ros::Subscriber subTP = nh.subscribe("targetpose", 1000, &pose2DMsg);
ros::Publisher pubTwist = nh.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel", 1000);

//initialize objects
tf2_ros::Buffer buffer;
tf2_ros::TransformListener listener(buffer);
geometry_msgs::TransformStamped ts;
geometry_msgs::Twist pose;

ros::Rate rate(5);

    while(ros::ok()) {

    ros::spinOnce();
       
       try {
          ts = buffer.lookupTransform("odom", "base_link", ros::Time(0));
       }
       catch(tf2::TransformException &ex) {
	      ROS_WARN("%s", ex.what());
              ros::Duration(1.0).sleep();
	      continue;
       }      
    
     ROS_INFO_STREAM("Obtained transformation: " << ts);
     
     //current pose minus target pose
     float xTransform = x-ts.transform.translation.x;
     float yTransform = y-ts.transform.translation.y;
     float thetaTransform = theta-ts.transform.rotation.z;

    //error threshold check; within 0.2m and 10 degrees
    if (abs(xTransform) < 0.2 && abs(yTransform) < 0.2 && (thetaTransform) > 0.175) {
        //if goal state is reached - stop & terminate
        pose.angular.z = M_PI/4;
        pose.linear.x = 0.0;
     	ROS_INFO_STREAM("Task Completed!");
	return 0;
     }
     else {
     //publish frame movements
     pose.linear.x = xTransform;
     pose.linear.y = yTransform;
     pose.angular.z = thetaTransform;
     pubTwist.publish(pose);
     rate.sleep();
     }
   }
return 0;
}
