# Installing the ESP32 Board in Arduino IDE (Windows, Mac OS X, Linux)

## Installing ESP32 Add-on in Arduino IDE 

1. In your Arduino IDE, go to **File**> **Preferences**

   ![](img\GettingStarted\GS1.png)

   

2. Enter **https://dl.espressif.com/dl/package_esp32_index.json** into the “Additional Board Manager URLs” field as shown in the figure below. Then, click the “OK” button:

   ![](img\GettingStarted\GS2.png)

3. Open the Boards Manager. Go to **Tools** > **Board** > **Boards Manager…**

   ![](img\GettingStarted\GS3.png)

4. Search for **ESP32** and press install button for the “**ESP32 by Espressif Systems**“:

   ![](img\GettingStarted\GS4.png)

5. That’s it. It should be installed after a few seconds.

   ![](img\GettingStarted\GS5.png)

### Program Upload

It was chosen to upload the program on the ESP32 using an [USB UART cable with FTDI chip](https://fr.rs-online.com/web/p/cables-raspberry-pi/7676200/). 

When try to upload a new sketch to your ESP32 in the Arduino IDE, it may fail to connect to your board saying ‘**A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header**’.

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Failed-to-connect-to-ESP32-Error-while-Uploading-Sketch-in-Arduino-IDE.png" alt="Dual-brige " width="500" />

Hold-down the **RESET** and **BOOT** button in your ESP32 board, then release  **RESET** then **BOOT** button. The ESP32 enters **BOOT** mode. After uploading a new sketch, press the **RESET** button to restart the ESP32 and run the new uploaded sketch.

[Back to main page](/README.md)

## Sources

- [Installing the ESP32 Board in Arduino IDE (Windows, Mac OS X, Linux)](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

