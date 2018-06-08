# iD Tech ROB4 - ROSJet

ROS structure and Arduino libraries for the course robot.

## Installation

For installing and configuring your Jetson board for the Jet robot, see the INSTALLATION.md file.
Hopefully, installation runs smoothly. If not, try the repository for 2017 hosted at:
github.com/iDTechHub/iD-Tech_ROB4-Jetson

## Running rosjet

For Gazebo Simulation:
```
roslaunch jet_bringup jet_gazebo.launch
```

For Real Robot:
```
roslaunch jet_bringup jet_real.launch
```
## Changelog

Changes from 2017 to 2018 content:
- 2017 nodes and packages moved into a folder: src/jetlabs/2017 Labs
- 2018 example packages provided. These were used in the testing and creation of this year's content. Note: They may be incomplete!
- The files in rosjet may have received minor changes during the development phase. Places for changes should be noted in the Developer Notes: ROS in the Game Plan instructor guides.
