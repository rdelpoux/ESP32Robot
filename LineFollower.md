# Line follower tracking controller

The main goal of this session is to be able to follow the black line using linear control theory ! In order to build the controller, it is required to understand the behavior of the robot and build a mathematical model. 

## System modeling

The robot is composed of two independent motors on the same axis of rotation and a free wheel. Orientation is achieved by the difference in movement between the two propulsion wheels. The posture of the robot is defined by (x, y,φ). Let us define the following variables : 

- ω1 and ω2 are respectively the angular speed [rad/s] of wheel 1 and wheel 2, measured by the encoder.
- r = 60 mm  is the radius of the wheels 
- v1 and v2 are the linear speed of each  wheel
- d = 0.18 m is the distance between the wheels 

The linear speed of the system is computed via the measured angular speed : 

- v1 = r ω1 ;
- v2 = r ω2;

 The linear speed of the robot (the center of mass) along xr (frame of reference attached to the robot ): 

- v_moy = (v1+v2)/2 

The system does not move along yr (frame of reference attached to the robot )  the speed according to yr is therefore null. 

The angle of rotation of the robot is given by the following relationship :

- φ = r /d( θ2- θ1)

<img src="img/LineFollower/schema_robot.png" alt="schema_robot" style="zoom:150%;" />

​											 Figure : representation of the two-wheeled robot. 

**Using matlab/simulinlk, based on the model proposed at the previous Lab for the speed control, propose a model for the new system **

## Control 

The objective is to propose a angle controller the track the line on the floor.

- Based on the model, propose a control law making it possible to control the angle to 0.
- You will propose specifications to be respected. 
- Using Matlab/Simulink, propose a control scheme and test the proposed control law.

## Experimental validation

Download the files for the lab : [download the code](/Programmes/ControlRobotESPRaspi_AP.zip). 

- Use the arduino IDE to implement a discretized version of your control law and check the performance in close loop.
- Record the experimental data of the system, plot them on Simulink and discuss compliance with the specifications.
