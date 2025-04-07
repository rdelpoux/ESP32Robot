#include <WiFi.h>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "frame.hpp"

#include "moteur.hpp"
#include "types.h"
#include "robotnumber.h"

#include "ESP32Encoder.h"

extern "C" {
#include "Filter0.h"
}



#define REDUCTION_RATIO (53.0f)
#define NBR_FRONT (12.0f)



const char* ssid = "Robot";
const char* password =  "123456789"; // choose only numeric password

WiFiServer server(80);
WiFiClient client;
bool clientConnected = false;

// Functions prototypes
void periodicControlTask( void *pvParameters );
void periodicWifiTask( void *pvParameters );
uint16_t tsControl = 10;
uint16_t tsWifi = 100;

// Global Variables Free RTOS
const int pinControlTask  = 18;
const int pinWifiTask  = 19;

/* Com */

Frame frame_in(&client);
Frame frame_out(&client);


// Declare motors
Moteur moteur1;
Moteur moteur2;
uint8_t motor1Enable  = 32;
uint8_t motor1Dir     = 16;
uint8_t motor2Enable  = 33;
uint8_t motor2Dir     = 17;


// Encoder
ESP32Encoder encoder1;
ESP32Encoder encoder2;

uint8_t S1A = 25;
uint8_t S1B = 27;
uint8_t S2A = 26;
uint8_t S2B = 14;

float deltaPos;
void formatVel();



int cmdMode;

void setup() {

  /*
     Communication Serie et wifi (https://techtutorialsx.com/2017/11/13/esp32-arduino-setting-a-socket-server/)
  */

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Setup start");

  // Wi-Fi config
  Serial.println("\n[INFO] Configuring access point");
  //WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("[INFO] Started access point at IP ");
  Serial.println(WiFi.softAPIP());


  server.begin();

  // Configure Motors
  moteur1.config(motor1Enable, motor1Dir, true, 30);
  moteur2.config(motor2Enable, motor2Dir, false, 30);
  moteur1.run();
  moteur2.run();

  // Configure Encoder
  // Encoders Config
  // Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  // Configure encoder 1
  encoder1.attachFullQuad(S1A, S1B);
  // Configure encoder 2
  encoder2.attachFullQuad(S2B, S2A);
  // clear the encoder's raw count and set the tracked count to zero
  encoder1.clearCount();
  encoder2.clearCount();

  deltaPos = 2.0f * PI / (NBR_FRONT * REDUCTION_RATIO);



  /*
     Free RTOS (http://tvaira.free.fr/esp32/esp32-freertos.html)
  */
  pinMode(pinControlTask, OUTPUT);
  pinMode(pinWifiTask, OUTPUT);
  xTaskCreate(periodicControlTask, "periodicControlTask", 10000, NULL, 8, NULL);
  xTaskCreate(periodicWifiTask, "periodicWifiTask", 10000, NULL, 9, NULL);



}

void loop() {
  delay(1000);
}


// Control variables
float pos1 = 0;
float pos2 = 0;
float vel1 = 0;
float vel2 = 0;
float com1 = 0 ;
float com2 = 0;
float u = 0;
float vref = 0;
float v = 0;

s32 data_0;
s32 data_1;
s32 data_2;

float ref_0;
float ref_1;
float ref_2;


/*

   Mode Open Loop

*/
void mode_ol() {
  u = ref_0;
  com1 = u;
  com2 = u;
  data_0 = 1000 * u;
  data_1 = 1000 * vel1;
  data_2 = 1000 * vel2;

}


/*

   Mode Step

*/
int nbr_ticks_step = 0;
void mode_step() {

  nbr_ticks_step ++;
  if (nbr_ticks_step <= 50) {
    u = 0;
  } else {
    if (nbr_ticks_step <= 250) {
      u = ref_0;
    }
    else {
      u = 0;
      cmdMode = MODE_OFF;
    }

  }
  com1 = u;
  com2 = u;
  // Save data
  data_0 = 1000 * u;
  data_1 = 1000 * vel1;
  data_2 = 1000 * vel2;

}

/*

   Mode Closed Loop

*/

void mode_cl() {



  data_0 = 1000 * 0;
  data_1 = 1000 * 0;
  data_2 = 1000 * 0;

}




/*

   Periodic Control Task

*/
void periodicControlTask( void *pvParameters )
{
  const char *pcTaskName = "Periodic Control Task";
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for ( ;; )
  {
    digitalWrite(pinControlTask, HIGH);
    //delay(1);
    //Serial.println("ControlTask");
    
    // Read Inputs
    pos1 = deltaPos * encoder1.getCount();
    pos2 = deltaPos * encoder2.getCount();

    vel1 = deltaPos * 100 * encoder1.getDt();
    vel2 = deltaPos * 100 * encoder2.getDt();
    formatVel();



    // Update Control

    switch (cmdMode) {
      case MODE_OFF :
        com1 = 0;
        com2 = 0;
        break;
      case MODE_OL :
        mode_ol();
        break;
      case MODE_STEP :
        mode_step();
        break;
      case MODE_CL :
        mode_cl();
        break;
    }









    // Write outputs
    moteur1.commande(com1);
    moteur2.commande(com2);


    frame_out.clear();

    if (clientConnected) {
      switch (cmdMode) {
        case MODE_STEP :
        case MODE_OL :
        case MODE_CL :
          frame_out.set_Cmd(CMD_SEND_DATA);
          frame_out.set_Data(data_0, 0);
          frame_out.set_Data(data_1, 1);
          frame_out.set_Data(data_2, 2);
          frame_out.set_checksum();
          frame_out.send_frame();
          break;
      }

    }

    digitalWrite(pinControlTask, LOW);
    vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(tsControl) ); // every 10 ms
  }
}


/*

   Periodic Wifi Task

*/
void periodicWifiTask( void *pvParameters )
{
  bool retval;
  const char *pcTaskName = "Periodic Wifi Task";
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  client = server.available();
  Serial.println("Client disconnected");

  int x;
  int countFrame;

  for ( ;; )
  {
    digitalWrite(pinWifiTask, HIGH);
    //Serial.println("Wifi Task");
    if (client.connected()) {
      if(!clientConnected)
        Serial.println("Client connected");
      clientConnected = true;
      //Receive Frame in
      retval = frame_in.recev_frame();
      if (retval) {
        switch (frame_in.get_Cmd()) {
          case CMD_MODE_OFF:
            cmdMode = MODE_OFF;
            Serial.println(" MODE OFF\n");
            break;
          case CMD_MODE_OL:
            cmdMode = MODE_OL;
            Serial.println(" MODE OL\n");
            break;
          case CMD_MODE_STEP:
            cmdMode = MODE_STEP;
            nbr_ticks_step = 0;
            Serial.println(" MODE STEP\n");
            break;
          case CMD_MODE_CL:
            cmdMode = MODE_CL;
            Serial.println(" MODE CLOSED LOOP\n");
            break;
        }
        ref_0 = 0.001 * (float) frame_in.get_data(0);
        ref_1 = 0.001 * (float) frame_in.get_data(1);
        ref_2 = 0.001 * (float) frame_in.get_data(2);
        Serial.println("ref " + String(ref_0) + " " + String(ref_1) + " " + String(ref_2));

      }
      frame_in.clear();

      }
      else {
      client.stop();
      if(clientConnected)
        Serial.println("Client disconnected");
      clientConnected = false;
      client = server.available();
      }



    

    digitalWrite(pinWifiTask, LOW);
    vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(tsWifi) ); // every 100 ms
  }
}


void formatVel() {
  Filter0_U.u1 = vel1;
  Filter0_U.u2 = vel2;
  Filter0_step();
  vel1 = Filter0_Y.y1;
  vel2 = Filter0_Y.y2;
}
