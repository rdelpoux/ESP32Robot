# DC Motor with encoder

The mobile robot is made up of two [DC motors with encoders](https://store.digilentinc.com/dc-motor-gearbox-1-53-gear-ratio-custom-6v-motor-designed-for-digilent-robot-kits/) and two [2A-H-bridge](https://reference.digilentinc.com/reference/pmod/pmodhb5/reference-manual)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moteur-reducteur-avec-encodeur.png" alt="motor" width="300" />

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/pmodhb5-0.png" alt="Dual-brige " width="150" />

The H-bridge is a PmodHB5 whose block block diagram is :

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Pmodblockdiagram.png" alt="Dual-brige " width="400" />

The PmodHB5 utilizes a full H-Bridge circuit to allow users to drive DC motors from the system board. Two sensor feedback pins are incorporated into the motor connection header.

### H-bridge

The H-bridge circuit principle is the following : 

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Hbridge.png" alt="Dual-brige " width="700" />

#### PWM control code

The following steps detail how to control the DC motor using PWM on ESP32.

- Declaring motor pins 

For motor pins table, refer the the [system description page](/SystemDescription.md). First define the GPIOs the motor pine are connected to.

```c
int motor1Enable = 32;
int motor1Dir = 16;
int motor2Enable = 33;
int motor2Dir = 17;    
```

- Program **setup()**

In the **setup()**, fisrt set the motor pins as outputs.

```c
pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(enable1Pin, OUTPUT);
```

 

### Encoder

For this section refer to [PJRC website](https://www.pjrc.com/teensy/td_libs_Encoder.html) : Encoders can sense movement in either direction, by detecting holes or marks as they move past 2 positions.  When the blue disc in the diagram below spins clockwise, the changes are first detected by pin 1, and then by pin 2.  When it spins counterclockwise, pin 2 is first to detect changes.  This scheme is called "quadrature encoding" because the waveforms detected by the 2 pins are 90 degrees out of phase.

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos1.png" alt="Dual-brige " width="500" />

## Sources

- ["ESP32 with DC Motor and L298N Motor Driver – Control Speed and Direction" ](https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/)
- [PJRC Electronic Projects Components Available Worldwide](https://www.pjrc.com/teensy/td_libs_Encoder.html)

