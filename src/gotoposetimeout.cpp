#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//global frame variables
double xPose = 0.0;
double yPose = 0.0;
double thetaPose = 0.0;

//function to handle user input for frames
void pose2DMsg(const geometry_msgs::Pose2D&msg) {

ROS_INFO_STREAM("Messages received!");
xPose = msg.x;
yPose = msg.y;
thetaPose = msg.theta;

}

//main function
int main(int argc,char **argv) {

    //initialize ros node
    ros::init(argc,argv,"gotopose");
    ros::NodeHandle nh;

    //subscribe to topic targetpose & call user input function
    ros::Subscriber subTP = nh.subscribe("targetpose", 1000, &pose2DMsg);

    //initialize base move
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
	ac("move_base",true);
    ROS_INFO_STREAM("Waiting for server to be available...");
    
    //connected to the server
    while(!ac.waitForServer()) {}
    ROS_INFO_STREAM("done!");

    //initialize move base object 
    move_base_msgs::MoveBaseGoal goal;

    //loop
    while(ros::ok()) {

    ros::spinOnce();
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    
    //pass through frame positons from function
    goal.target_pose.pose.position.x = xPose;
    goal.target_pose.pose.position.y = yPose;
    goal.target_pose.pose.orientation.w = thetaPose;

    //publish positions essentially
    ac.sendGoal(goal);
    ac.waitForResult(ros::Duration(5.0));	

    //if goal isn't reached within 5 seconds, preempt & print failure
    if (ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
      ac.cancelGoal();
     ROS_INFO_STREAM("Failed to reach goal within 5 seconds!");
    }  
    }
    return 0;    
}

