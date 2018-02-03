#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void laserScan(const sensor_msgs::LaserScan&scan) {

ROS_INFO_STREAM("Scanner activates!");

//initializations
int i = 0;
float field_ranges = scan.ranges[1000];

//loop through the entire field range
while(i < scan.ranges.size()) {
    field_ranges = scan.ranges[i];
    ROS_INFO_STREAM("Range scan: " << field_ranges);
    //iterates
    i++;
}
}

int main(int argc, char ** argv) {

ros::init(argc,argv,"LaserScanner");
//initialize node
ros::NodeHandle nh;
//subscribe to topic /scan
ros::Subscriber sub = nh.subscribe("/scan", 1000, &laserScan);
//spin
ros::spin();
}
