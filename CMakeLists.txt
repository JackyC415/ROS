cmake_minimum_required(VERSION 2.8.3)
project(labpkg)

find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs sensor_msgs tf2 tf2_ros)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable (sendtime src/sendtime.cpp)
add_executable (receivetime src/receivetime.cpp)
add_executable (square src/square.cpp)
add_executable (getlaser src/getlaser.cpp)
add_executable (getpose src/getpose.cpp)
add_executable (gotopose src/gotopose.cpp)

target_link_libraries(sendtime ${catkin_LIBRARIES})
target_link_libraries(receivetime ${catkin_LIBRARIES})
target_link_libraries(square ${catkin_LIBRARIES})
target_link_libraries(getlaser ${catkin_LIBRARIES})
target_link_libraries(getpose ${catkin_LIBRARIES})
target_link_libraries(gotopose ${catkin_LIBRARIES})
