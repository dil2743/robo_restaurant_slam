#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;
//callback function for the service 
/*
*This will publish the command to topic /cmd_vel
*After publishing the command we are simply returning the velocity as Response 
*/
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{
/*
*limit velocity 
*/
    float  max_linear_velocity = 1.0 ,max_angular_velocity = 0.6;
    if(abs(req.linear_x)> max_linear_velocity ){
        if(req.linear_x < 0) req.linear_x= -1 * max_linear_velocity;
        else req.linear_x = max_linear_velocity;
    }
    if(abs(req.angular_z) > max_angular_velocity){
        if(req.angular_z < 0) req.angular_z = -1 * max_angular_velocity ;
        else req.angular_z = max_angular_velocity;
    }
    ROS_INFO("Velocity Requested - linear:%1.2f, angular:%1.2f", (float)req.linear_x, (float)req.angular_z);

	// Create a motor_command object of type geometry_msgs::Twist
	geometry_msgs::Twist motor_command;
	//since the robot fame is reversed so mapping velocities 
	motor_command.linear.x = (-1.0 * req.linear_x);
	motor_command.angular.z = (-1.0 * req.angular_z);
	// Publish angles to drive the robot
	motor_command_publisher.publish(motor_command);

    // Return a response message
    res.msg_feedback = "velocity set at  - linear: " + std::to_string((float)req.linear_x) + " , angular: " + std::to_string((float)req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
}


int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send velocity commands");

    ros::spin();

    return 0;
}
