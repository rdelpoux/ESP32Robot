[Back to main page](/README.md)

# System description <a name="systemdescription"></a>

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/MobileRobile.jpg" alt="Dual-brige " width="400" />

[Back to main page](/README.md)

## System

The system is composed of 

- [2A-H-bridge](https://reference.digilentinc.com/reference/pmod/pmodhb5/reference-manual)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/pmodhb5-0.png" alt="Dual-brige " width="150" />

- [Two motors with encoders](https://store.digilentinc.com/dc-motor-gearbox-1-53-gear-ratio-custom-6v-motor-designed-for-digilent-robot-kits/)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moteur-reducteur-avec-encodeur.png" alt="motor" width="300" />

- [7.4V Lithium-Ion 2.6Ah](https://fr.rs-online.com/web/p/blocs-batteries-rechargeables/1449410/) battery

- [Motor support](https://www.lextronic.fr/support-pour-moteurs-30627.html)

![support](https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/support-pour-moteurs.jpg)

- [Motor hubs](https://www.lextronic.fr/moyeux-pour-moteurs-pololu-30809.html)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moyeux-pour-moteurs-pololu.jpg" alt="moyeux " width="150" />

- [60 mm wheels](https://www.lextronic.fr/paire-de-roues-diametre-60-mm-30817.html)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/paire-de-roues-diametre-60-mm.jpg" alt="wheel " width="300"/>

- [Free wheel](https://www.manomano.fr/catalogue/p/litzee-transfert-a-billes-roulettes-pour-meubles-roulettes-transfert-a-rouleaux-unites-de-transfert-a-billes-fer-galvanise-avec-boules-en-nylon-pour-transmission-meubles-fauteuil-roulant-6-pieces-28320695?g=1&referer_id=689880&cq_src=google_ads&cq_cmp=11057446537&cq_con=110150695580&cq_term=&cq_med=pla&cq_plac=&cq_net=g&cq_pos=&cq_plt=gp&cq_plt=gp&gclid=Cj0KCQiA0-6ABhDMARIsAFVdQv8q6O9rFnHw9-YfIDL3XiyYXy5AE14RHB-vroiU9LCYbMjPGpgr8QIaAvA5EALw_wcB#/)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/free-wheel.jpg" alt="free-wheel " width="200"/>

[Back to main page](/README.md)

## Controller board

The chosen ESP32 is a ESP32-WROOM-32D and the datasheet is available [here](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf). It was  mounted on a custom PCB.

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Chargeur_ESP32.png" alt="Dual-brige " width="400" />

The PCB features are the following :

- Drive 2 DC motors
- Read 2 DC motors encoder
- Charge Battery

### PCB description

The principle scheme of the PCB is :

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/PCBPrinciple.png" alt="Dual-brige " width="800" />

Specifically, the routing of the ESP 32 is 

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/ESPMod.png" alt="Dual-brige " width="800" />

### Pinout

| Name | Description                              | ESP32  Pinout |
| ---- | ---------------------------------------- | ------------- |
| Dir1 | Motor 1 direction (0 forward, 1 reverse) | IO16          |
| Dir2 | Motor 2 direction (0 forward, 1 reverse) | IO17          |
| En1  | Enable motor 1 (PWM)                     | IO32          |
| En2  | Enable motor 2 (PWM)                     | IO33          |
| S1A  | Motor 1 Sensor A feedback pin            | IO25          |
| S1B  | Motor 1 Sensor B feedback pin            | IO27          |
| S2A  | Motor 2 Sensor A feedback pin            | IO26          |
| S2B  | Motor 2 Sensor B feedback pin            | IO14          |

### Program Upload

It was chosen to upload the program on the ESP32 using an [USB UART cable with FTDI chip](https://fr.rs-online.com/web/p/cables-raspberry-pi/7676200/). 

When try to upload a new sketch to your ESP32 in the Arduino IDE, it may fail to connect to your board saying ‘**A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header**’.

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Failed-to-connect-to-ESP32-Error-while-Uploading-Sketch-in-Arduino-IDE.png" alt="Dual-brige " width="500" />

Hold-down the **RESET** and **BOOT** button in your ESP32 board, then release  **RESET** then **BOOT** button. The ESP32 enters **BOOT** mode. After uploading a new sketch, press the **RESET** button to restart the ESP32 and run the new uploaded sketch.



[Back to main page](/README.md)

## Sources 

- [https://lastminuteengineers.com/esp32-arduino-ide-tutorial/](https://lastminuteengineers.com/esp32-arduino-ide-tutorial/)

[Back to main page](/README.md)