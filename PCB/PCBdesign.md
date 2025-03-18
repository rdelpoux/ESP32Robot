# PCB design

## ESP 32

The chosen ESP32 is a ESP32-WROOM-32D and the datasheet is available [here](https://github.com/rdelpoux/ESP32Robot/blob/main/PCB/datasheets/esp32_wroom_32d_esp32_wroom_32u_datasheet_en-1365844.pdf). 

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/ESP32-WROOM-32D_Pin_Layout.png" alt="PinLayout " width="300" />



<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/ESPPinout.png" alt="PinLayoutSheme " width="800" />

## Program upload

It was chosen to upload the program on the ESP32 using an [USB UART cable with FTDI chip](https://fr.rs-online.com/web/p/cables-raspberry-pi/7676200/). 

## Dual half bridge

The dual half bridge datasheet can be found [here](https://github.com/rdelpoux/ESP32Robot/blob/main/PCB/datasheets/pmoddhb1_sch.pdf).

The dual half bridge can be connected to the PCB. Pmod port is an open 12-pin interface arranged in 2 rows of 6 pins. The PCB include the following connector :  

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/pmod.png" alt="PinLayout " width="150" />

The pins are arranged as : 

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/pmod_pins.jpeg" width="200" />

For the Dual half bridge, the pins are the following :

| Data pins | Motor 1 | Data pins | Motor 2 |
| --------- | ------- | --------- | ------- |
| 0         | EN1     | 4         | EN2     |
| 1         | DIR1    | 5         | DIR2    |
| 2         | S1A     | 6         | S2A     |
| 3         | S1B     | 7         | S2B     |

## Battery Management

The system is powered by a [7.4V Lithium-Ion 2.6Ah](https://fr.rs-online.com/web/p/blocs-batteries-rechargeables/1449410/) battery. The PCB embed a battery charger. 

Charger example :

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/ChargeurBatterie.png" width="800" />

