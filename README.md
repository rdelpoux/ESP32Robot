# Lab : Mobile Robot ESP32

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/MobileRobile.jpg" alt="Dual-brige " width="400" />

This repository is dedicated to the development of a new mobile robot Lab proposed for student in the French engineering school [INSA Lyon](www.insa-lyon.fr). In a COVID context the objective is to propose automatic control lab which can be taught both in class and remotely in the event of confinement. The constraint is to be able to illustrate the basic automatic control principles on a simple system, without the need for software requiring a significant computing capacity.  During the lab, Matlab/Simulink:registered:  can be used to do the corrector synthesis, but the students can access it remotely using a VPN.

Given the specifications, our choice is directed to an ESP32 controller. This low cost device combines a dual core 160Mhz CPU and Wi-Fi. This makes it possible to embed a web server and that the students can realize the entire Lab using only an Internet browser.  

## Content

- [Contributors](#Contributors)
- [Lab objective](#objective)
- [Session 1](#session1)
- [Session 2](#session2)
- [Session 3](#session3)
- [Sources](#sources)
- [License](#license)

## Contributors <a name="contributors"></a>

- Romain Delpoux (Romain.Delpoux at insa-lyon.fr), Associate Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Aboubacar Ndoye (Aboubacar.Ndoye at insa-lyon.fr), PhD student, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Cédric Escudero (Cedric.Escudero at insa-lyon.fr), Assistant Professor, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Pascal Bevilacqua (pascal.bevilacqua at insa-lyon.fr), Engineer, INSA de Lyon, Laboratoire Ampère UMR CNRS 5005.
- Christophe Ducat (christophe.ducat at insa-lyon.fr), Engineer, INSA de Lyon, CETHIL UMR 5008

## Lab objective <a name="objective"></a>

The Lab is divided into 3 sessions of 4 hours. 

1. Getting to know the system and the control environment (4h)
2. Robot speed control (4h)
3. Robot trajectory tracking (4h)

At the end of this project, students should be able to :

- Drive a DC motor with encoder
- Understand how a real-time system works  (Tasks, Priorities, ...) 
- Identify a linear system 
- Simulate a linear system and compare with experimental data 
- Design and implement a control law (Simulation + Experimentation)
- Enjoy

## Session 1 <a name="session1"></a>

The objective of this first session is to discover the system. At the end of the session, the student should have 

- Learned about the Arduino programming environment for ESP32.
- Run both motors (forward, backward).
- Use encoders.
- Use FreeRTOS, for real time control.

### System description

For system description goto : [System description page](/SystemDescription.md)

### Getting Started with the ESP32 Development Board

### [Preparing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/getting-started-with-esp32/)

There’s an add-on for the Arduino IDE allows you to program the ESP32 using the Arduino IDE and its programming language. Follow one of the  next tutorials to prepare your Arduino IDE:

- [**Windows** instructions – Installing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
- [**Mac and Linux** instructions – Installing the ESP32 Board in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/)

### DC motor with encoder

The tutorial to drive the DC motor can be found here : [DC Motor with encoder](\Motorwithencoder.md)

## Session 2 <a name="session2"></a>

TBD

## Session 3 <a name="session3"></a>

TBD

## Sources <a name="sources"></a>

- [https://randomnerdtutorials.com](https://randomnerdtutorials.com)
- 

## License <a name="license"></a>

The proposed materials on this repository are free of charge to use and is openly distributed, but note that

1.  Copyright owned by Romain Delpoux.
2.  The algorithms, or forks of the algorithms may not be re-distributed as a part of a commercial product unless agreed upon with the copyright owner. 
4. This work is distributed in the hope that it will be useful, but without any warranty, without event the implied warranty of merchantability or fitness for a particular purpose.







