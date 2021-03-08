# ROS-Localization-AMCL
Robotic simulation project using ROS (Robot Operating System), Gazebo, RViz simulation environment using AMCL.

## Project Description

This project contains 3 packages
`teleop_twait_kwyboard` to drive robot using keyboard

`my_robot` this package contains robot discription and lauch files 

`robo_restaurant` this conatins  `amcl node`,`localization.launch`, `mapping.lainch` and `teleop.launch`

### rtab_file
* rtab map file can be [found here](https://drive.google.com/file/d/1YZp7_K-xoLZBWqIt0dvZp4jH4DDboROO/view)
## Running the Project


```bash
$ cd ~/catkin_ws
$ cd src
```
clone the repo in scr folder of your workspace 
```bash
$ git clone https://github.com/dil2743/robo_restaturant_slam
$ cd ..
$ catkin_make
$ source devel/setup.bash
```

And then run the following command -

``` bash
$ roslaunch robo_restaurant localization.launch
```
this will launch the `gazebo world` and `rviz` 

``` bash
$ roslaunch robo_restaurant mapping.launch
```
this will lauch the mapping node 
``` bash
$ roslaunch robo_restaurant teleop.launch
```
this will launch telepo node


Mobile Robot in Gazebo World with Environment Obstacles

<p align="center"> <img src="https://github.com/dil2743/robo_restaurant_slam/blob/master/image/new_world.jpg"> </p>

Rviz pose estimation 

<p align="center"> <img src="https://github.com/dil2743/robo_restaurant_slam/blob/master/image/rtabmap.PNG"> </p>


Helpful resource for better understanding AMCL [here](
http://roboticsknowledgebase.com/wiki/state-estimation/adaptive-monte-carlo-localization/)

