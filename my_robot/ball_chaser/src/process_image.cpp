#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
        ROS_INFO_STREAM("Publishing command to service ");

	ball_chaser::DriveToTarget command;
	command.request.linear_x = lin_x;
	command.request.angular_z = ang_z;
	
	if(!client.call(command)){
		ROS_ERROR("Failed to call service command_robot");	
	}
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    bool is_white_pixal = false;
    int location_of_pixal = -1;
    int boundry_size = img.step/3;
    float lin_x, ang_z;
	std::cout << "boundry_size : " << boundry_size << "height :" << img.height <<"step: "<<img.step ;
    for (int i = 0; i < img.height * img.step; i++) {
	//std::cout << "value : " << (uint8_t)img.data[i] ;
        if (img.data[i] == 255 && img.data[i+1] == 255 && img.data[i+2] == 255) {
            is_white_pixal = true;
	    int temp_data = (i % img.step)  ; //height
            location_of_pixal = temp_data;//i/temp_data;

	ROS_INFO_STREAM("############################### GOT YOU ####################");
            break;
        }
    }
    
    if( location_of_pixal >= 0 && location_of_pixal < boundry_size){
	// left frame
	ROS_INFO("Ball detected on left side %d",location_of_pixal);
	lin_x = 0.3;
	ang_z = -0.6;
		
    }else  if( location_of_pixal >= boundry_size && location_of_pixal < (2*boundry_size) ){
	// center frame	
	ROS_INFO("Ball detected on center %d",location_of_pixal);
	lin_x = 0.6;
	ang_z = 0.0;
    }else  if( location_of_pixal >= (2*boundry_size) && location_of_pixal <= (3*boundry_size)){
	// right frame	
	ROS_INFO("Ball detected on right side %d",location_of_pixal);
	lin_x = 0.3;
	ang_z = 0.6;
    }else{
	ROS_INFO("Oops no Ball found %d",location_of_pixal);
	lin_x = 0.0;
	ang_z = 0.0;
    }
	drive_robot(lin_x,ang_z);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
