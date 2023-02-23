#!/usr/bin/env python
import rospy 
import numpy as np
from challenge1.msg import signal_msg


if __name__ == '__main__':
	rospy.init_node("signal_generator")
	signal_pub = rospy.Publisher("signal", signal_msg, queue_size=10)

	A = 5
	
	init_time = rospy.get_time()
	msg = signal_msg()
	rate = rospy.Rate(10)

	while not rospy.is_shutdown():
		t = rospy.get_time() - init_time
		y = A + np.sin(t) * np.pi
		
		msg.time_x = t
		msg.signal_y = y

		rospy.loginfo(y)
		signal_pub.publish(msg)

		rate.sleep()

