# ROS-Localization-AMCL
Robotic simulation project using ROS (Robot Operating System), Gazebo, RViz simulation environment using AMCL.

## Project Description


Amcl (Adaptive Monte Carlo Localization) is a Robot Operating System (ROS) navigation package which utilizes particle filters to track the pose of a moving robot with a known 2D map.The robot is a differential drive robot with two caster wheels, a laser sensor, and a camera sensor

This project contains 3 packages
`teleop_twait_kwyboard` to drive robot using keyboard

`my_robot` this package contains robot discription and lauch files 

`robo_restaurant` this conatins  `amcl node`,`parameter` and `main_launch file`





## Running the Project


```bash
$ cd ~/catkin_ws
$ cd src
```
clone the repo in scr folder of your workspace 
```bash
$ git clone https://github.com/dil2743/robo_restaturant
$ cd ..
$ catkin_make
$ source devel/setup.bash
```

And then run the following command -

``` bash
$ roslaunch robo_restaurant robo_restaurant.launch
```
this will launch the `gazebo world` `Rviz` and `amcl_node`


Mobile Robot in Gazebo World with Environment Obstacles

<p align="center"> <img src="image/gazebo_world.png"> </p>

Rviz pose estimation 

<p align="center"> <img src="image/wold_and_rviz.png"> </p>

<p align="center"> <img src="image/robot_pose_navGole.png"> </p>

Helpful resource for better understanding AMCL [here](
http://roboticsknowledgebase.com/wiki/state-estimation/adaptive-monte-carlo-localization/)

