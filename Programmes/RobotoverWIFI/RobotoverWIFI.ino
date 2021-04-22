#include "ESP32Encoder.h"
#include <WiFi.h>

/* Sources

   https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
   https://github.com/ESP32Encoder

*/

WiFiServer server(80);


// Change the name of the ssid otherwise, alle the robots will have the same name...
const char* ssid     = "robot1";

ESP32Encoder encoderA;
ESP32Encoder encoderB;

// Auxiliar variables to store the current output state
String outputForward = "off";
String outputLeft = "off";
String outputRight = "off";
String outputBackward = "off";

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";
String output28State = "off";
String output29State = "off";

// PWM
uint8_t motor1Enable  = 32;
uint8_t motor1Dir     = 16;
uint8_t motor1Channel = 0;
uint8_t motor2Enable  = 33;
uint8_t motor2Dir     = 17;
uint8_t motor2Channel = 1;

// Encoder
uint8_t S1A = 25;
uint8_t S1B = 27;
uint8_t S2A = 26;
uint8_t S2B = 14;

uint8_t posM1 = 0;
uint8_t posM2 = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Wi-Fi DC motor");

  // Wi-Fi config
  Serial.println("\n[INFO] Configuring access point");
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid);
  server.begin();

  Serial.print("[INFO] Started access point at IP ");
  Serial.println(WiFi.softAPIP());

  // Motors Config
  pinMode(motor1Enable, OUTPUT);
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
  pinMode(motor2Dir, OUTPUT);

  // Configure PWM signal ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(motor1Channel, 500, 8); // channel 0, 500Hz, 8-bits resolution
  ledcSetup(motor2Channel, 500, 8); // channel 1, 500Hz, 8-bits resolution

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor1Enable, motor1Channel); // attach channel 0 to motor 1
  ledcAttachPin(motor2Enable, motor2Channel); // attach channel 1 to motor 2

  // Encoders Config
  // Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors = UP;

  // Configure encoder A
  encoderA.attachFullQuad(S1A, S1B);
  // Configure encoder B
  encoderB.attachFullQuad(S2B, S2A);

  // clear the encoder's raw count and set the tracked count to zero
  encoderA.clearCount();
  encoderB.clearCount();





}

int dutyCycle = 100;

void motorForward(){
  // Define duty cycle
  ledcWrite(motor1Channel, dutyCycle);
  ledcWrite(motor2Channel, dutyCycle);
  // Choose direction
  digitalWrite(motor1Dir, HIGH);
  digitalWrite(motor2Dir, LOW);
}

void motorLeft(){
  // Define duty cycle
  ledcWrite(motor1Channel, dutyCycle/2);
  ledcWrite(motor2Channel, dutyCycle/2);
  // Choose direction
  digitalWrite(motor1Dir, LOW);
  digitalWrite(motor2Dir, LOW);    
}

void motorRight(){
  // Define duty cycle
  ledcWrite(motor1Channel, dutyCycle);
  ledcWrite(motor2Channel, dutyCycle);
  // Choose direction
  digitalWrite(motor1Dir, HIGH);
  digitalWrite(motor2Dir, HIGH);    
}

void motorBackward(){
  // Define duty cycle
  ledcWrite(motor1Channel, dutyCycle);
  ledcWrite(motor2Channel, dutyCycle);
  // Choose direction
  digitalWrite(motor1Dir, LOW);
  digitalWrite(motor2Dir, HIGH);
}

void motorStop(){
    // Define duty cycle
  ledcWrite(motor1Channel, 0);
  ledcWrite(motor2Channel, 0);
  // Choose direction
  digitalWrite(motor1Dir, LOW);
  digitalWrite(motor2Dir, LOW);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("MotorForward");
              outputForward = "on";
              outputLeft = "off";
              outputRight = "off";
              outputBackward = "off";
              motorForward();
            } 

            if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("MotorLeft");
              outputForward = "off";
              outputLeft = "on";
              outputRight = "off";
              outputBackward = "off";
              motorLeft();
            } 


            if (header.indexOf("GET /28/on") >= 0) {
              Serial.println("MotorRight");
              outputForward = "off";
              outputLeft = "off";
              outputRight = "on";
              outputBackward = "off";
              motorRight();
            } 

            if (header.indexOf("GET /29/on") >= 0) {
              Serial.println("MotorBackward");
              outputForward = "off";
              outputLeft = "off";
              outputRight = "off";
              outputBackward = "on";
              motorBackward();
            } 

            if (header.indexOf("GET /26/off") >= 0 || header.indexOf("GET /27/off") >= 0 || header.indexOf("GET /28/off") >= 0 || header.indexOf("GET /29/off") >= 0) {
              Serial.println("MotorStop");
              outputForward = "off";
              outputLeft = "off";
              outputRight = "off";
              outputBackward = "off";
              motorStop();
            }
            


            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println(".marge {margin-left: 10em;}");
            client.println(".marge2 {margin-left: 2em;}");
            client.println("</style></head>");

            // Web Page Heading
            client.println("<body><h1><p>ESP32Robot</p> <p>DC motor drive over Wi-Fi</p></h1>");

            // Display current pos
            client.println("<p>Forward</p>");
            // If the output26State is off, it displays the ON button
            if (outputForward == "off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Left <span class=\"marge\">Right</span></p>");
           if (outputLeft == "off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a><span class=\"marge2\">");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a><span class=\"marge2\">");
            }
           if (outputRight == "off") {
              client.println("<a href=\"/28/on\"><button class=\"button\">ON</button></a></span></p></p>");
            } else {
              client.println("<a href=\"/28/off\"><button class=\"button button2\">OFF</button></a></span></p></p>");
            }
            
            client.println("<p>Backward</p>");
            // If the output29State is off, it displays the ON button
            if (outputBackward == "off") {
              client.println("<p><a href=\"/29/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/29/off\"><button class=\"button button2\">OFF</button></a></p>");
            }




            

/*
            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>Recule - State " + outputRecule + "</p>");
            // If the output27State is off, it displays the ON button
            if (outputRecule == "off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            */
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");


  }
}
