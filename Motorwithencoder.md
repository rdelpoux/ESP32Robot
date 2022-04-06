[Back to main page](/README.md)

# DC motor with encoder

The mobile robot is made up of two [DC motors with encoders](https://store.digilentinc.com/dc-motor-gearbox-1-53-gear-ratio-custom-6v-motor-designed-for-digilent-robot-kits/) and two [2A-H-bridge](https://reference.digilentinc.com/reference/pmod/pmodhb5/reference-manual)

<img src="img/moteur-reducteur-avec-encodeur.png" alt="motor" width="300" />

<img src="img/pmodhb5-0.png" alt="Dual-brige " width="150" />

[Back to main page](/README.md)

## PWM principle

The ESP32 has digital output only, while, to drive DC motor, it is necessary to apply analog voltage. It requires to convert digital to analog signals. For this we use a PWM (Pulse Width Modulation). The PWM is a technique used to reconstruct continuous signals using on / off circuits, e.g. Boolean outputs. A PWM signal is represented as :

<img src="img/PWMPrinciple.png" alt="Dual-brige " width="500" />

The principle is to generate high frequency rectangular pulse wave. Over a period **T**, the pulse width can take a value between 0 and T. The pulse width  divided by the period T is called the duty cycle and is denote <img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/alpha.png" width="15" /> on the figure. The average output voltage will therefore be equal to v (t) =  <img src="img/alpha.png" width="15" />Vcc. This average voltage is shown in red in the figure. 

The voltage delivered by the ESP32 rages between **0** et **3.3v**. Using a 8-bits resolution, the duty cycle ranges between **0** and **255**. In practice, a voltage between **-Vmax** and **Vmax** needs to be applied on the motor, done using an H bridge. 

### H-bridge

The H-bridge circuit principle is the following : 

<img src="img/Hbridge.png" alt="Dual-brige " width="700" />

The H-bridge is a PmodHB5 whose block block diagram is :

<img src="img/Pmodblockdiagram.png" alt="Dual-brige " width="400" />

The PmodHB5 utilizes a full H-Bridge circuit to allow users to drive DC motors from the system board. Two sensor feedback pins are incorporated into the motor connection header.

#### PWM control code 

The [LED control (LEDC)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html) peripheral is primarily designed to control the  intensity of LEDs, although it can also be used to generate PWM signals  for other purposes. It has 16 channels which can generate independent waveforms that can be  used.

The following steps detail how to control the DC motor using PWM on ESP32.

- Declaring motor pins 

For motor pins table, refer the the [system description page](/SystemDescription.md). First define the GPIOs the motor pine are connected to.

```c
int motor1Enable = 32;
int motor1Dir = 16;
int motor2Enable = 33;
int motor2Dir = 17;    
```

- Program **setup()** function

In the **setup()**, first set the motor pins as outputs.

```c
pinMode(motor1Enable, OUTPUT);
pinMode(motor1Dir, OUTPUT);
pinMode(motor2Enable, OUTPUT);
pinMode(motor2Dir, OUTPUT);
```

 Configure PWM signal is done by setting the PWM channel, frequency and resolution as follow :

```c
ledcSetup(pwmChannel, freq, resolution);
```

In our case, we're generating a PWM signal at 500Hz with a 8-bit resolution, on channel 0 for motor 1 and channel 1 for motor 2. 

Finally, the PWM signal is attached to the desired pin : 

```c
ledcAttachPin(motorxEnable, pwmChannel);
```

- **Moving the DC motor**

To apply different voltage to the motor, we need to change the PWM signal duty cycle. For that you use the ledcWrite()  function that accepts as arguments the PWM channel that is generating  the signal (not the output GPIO) and the duty cycle, as follows.

```c
ledcWrite(pwmChannel, dutyCycle);
```

- **Moving the DC motors forward or backwards**

To move the motor forward, you set motor**X**Dir pin to LOW, to move the motor backward, you set motor**X**Dir pin to HIGH.

```c
digitalWrite(motorXDir, LOW);
```

[Back to main page](/README.md)

## Encoder

Magnetic rotary encoders are devices that convert angular position into digital signals for use within measurement or control systems. Magnetic encoders use a combination of permanent magnets and magnetic sensors to detect movement and position. A typical construction uses magnets placed around the edge of a rotor  disc attached to a shaft and positioned so that the sensor detects  changes in magnetic field as the alternating poles of the magnet pass  over it. When disc in the diagram below spins clockwise, the changes are first detected by pin 1, and then by pin 2. When it spins counterclockwise, pin 2 is first to detect changes.  This scheme is called "quadrature encoding" because the waveforms detected by the 2 pins are 90 degrees out of phase.



<img src="img/encodermod.png" alt="Dual-brige " width="500" />

For an animation visit [PJRC website](https://www.pjrc.com/teensy/td_libs_Encoder.html).

### Encoder software measurement

On software side, the objective is to detect raising and falling edge. Without knowing the motor speed, the edge occurrence is unknown. To ensure that a program always caught the pulses from the  rotary encoder, so that it never misses a pulse, it would make it very  tricky to write a program to do anything else, because the program would need to constantly poll the sensor lines for the encoder, in order to  catch pulses when they occurred.  Using an interrupt can free the microcontroller to get some other work done while not missing the input.

- Pull-Up resistor

<img src="img/Pullup_Resistor.png" alt="Dual-brige " width="200" />

- Syntax

```c
pinMode(S1A , INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
```

- Parameters
  - **pin** : the ESP32 pin we want to attach the interrupt
  - **ISR** : the ISR to call when the interrupt occurs; this function must take no  parameters and return nothing. This function is sometimes referred to as an interrupt service routine.
  - **mode** defines when the interrupt should be triggered. Four constants are predefined as valid values:
    - **LOW** to trigger the interrupt whenever the pin is low,
    - **CHANGE** to trigger the interrupt whenever the pin changes value
    - **RISING** to trigger when the pin goes from low to high,
    - **FALLING** for when the pin goes from high to low.

### [ESP32 Pulse Counter](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html)

The ESP32 has a Pulse counter module. The PCNT (Pulse Counter) module is designed to count the number of  rising and/or falling edges of an input signal. Each pulse counter unit  has a 16-bit signed counter register and two channels that can be  configured to either increment or decrement the counter. Each channel  has a signal input that accepts signal edges to be detected, as well as a control input that can be used to enable or disable the signal input.  The inputs have optional filters that can be used to discard unwanted  glitches in the signal.

A library for the use of this module is available on [madhephaestus GITHUB Repository](https://github.com/madhephaestus/ESP32Encoder).

[Back to main page](/README.md)

## Sources

- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
- ["ESP32 with DC Motor and L298N Motor Driver – Control Speed and Direction" ](https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/)
- [Understanding Resolution in optical and magnetic Encoders ](https://www.elektronikpraxis.vogel.de/understanding-resolution-in-optical-and-magnetic-encoders-a-427263/)
- [Arduino attachInterrupt()](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
- [Pull-up resistor](https://en.wikipedia.org/wiki/Pull-up_resistor)

[Back to main page](/README.md)

