# Robotic_Foundations_Deliverables
Software Requirements:
  Ubuntu 18.04
  ROSMelodic

## Some Usefull code lines:
1.  Creating a pkg:    
  - cakin_create_pkg >name of the pkg< [depend1] [depend2] [depend3]
  - catkin_create_pkg basic_comms std_msgs rospy

2.  Creating a folder:
  - mkdir [folders_name]

3.  Creating a file:
  - touch [name]

4.  Giving permission to executable scripts
  - sudo chmod +x [name]

5.  Loading files
  - catkin_make
  - source devel/setup.bash

6.  To visualize the output of a node:
  - rostopic echo
  
7.  Execute a node
  - rosrun [package] [node]
  
8.  List the topics avialable
  - rostopic list
  
9.  Execute a launch File:
  - roslaunch [package] [name.launch]

  
