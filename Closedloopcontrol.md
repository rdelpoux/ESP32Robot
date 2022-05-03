# Closed loop control

## Getting started

Download the files for the lab : [download the code](/Programmes/ControlRobotESP_AP.zip). 

Plug the WIFI key into your computer.

- Open the Arduino project "ControlRobotESP_AP.ino"

- Configure Arduino plateform for ESP32 : 

  - There’s an add-on for the Arduino IDE allows you to program the ESP32 using the Arduino IDE and its programming language : [Getting Started](/GettingStarted.md)

- Modify this program by renaming the variable ssid :

  ```c
  const char* ssid = "Robot";
  ```

  This variable is the name of your robot and you have to choose a more specific name to avoid communication problems with other robots. For example, replace "robot" with "robots_names", where the names are your initials and those of your coworker.

- Load the program into the micro-controller.
- Start MATLAB and run the program "SimuESP32.slx".
- Double click on button "ESP32 APP". In the new window, clik on the red button "Connect".

## Required work 

### Modeling

- Propose a model which link the input voltage to the speed of the robot.

### Identification

- From a step response between the input voltage to the speed of the robot, identify a linear model of the system around a voltage u=3V. Justify this operating point
- Validate this model by comparing the measurements and the simulation of the model

### Control 

The objective is to propose a speed control of the robot. 

- Based on the model identified, propose a control law making it possible to control the speed. 
- Based on the model identified, propose a control law making it possible to control the speed. You will propose specifications to be respected. 

- Using Matlab/Simulink, propose a simulation scheme and test the proposed control law.
- Use the arduino IDE to implement a discretized version of your control law and check the performance in close loop.
- Record the experimental data of the system, plot them on Simulink and discuss compliance with the specifications.

