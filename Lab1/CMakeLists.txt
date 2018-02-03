cmake_minimum_required(VERSION 2.8.3)
project(labpkg)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS})

add_executable(sendtime src/sendtime.cpp)
add_executable(receivetime src/receivetime.cpp)
target_link_libraries(sendtime ${catkin_LIBRARIES})
target_link_libraries(receivetime ${catkin_LIBRARIES})

