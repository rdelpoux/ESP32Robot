
int motor1Enable = 32;
int motor1Dir = 16;
int motor1Channel = 0;
int motor2Enable = 33;
int motor2Dir = 17;    
int motor2Channel = 1;



void setup() {
  Serial.begin(115200);
  Serial.println("DC motor forward and bacward");
  
  // put your setup code here, to run once:
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // DC motor forward
  Serial.println("DC motor forward");
  // Define duty cycle
  ledcWrite(motor1Channel, 100);
  ledcWrite(motor2Channel, 100);
  // Choose direction
  digitalWrite(motor1Dir, LOW);
  digitalWrite(motor2Dir, LOW);

  delay(2000);
 
  // DC motor forward
  Serial.println("DC motor backward");
  // Define duty cycle
  ledcWrite(motor1Channel, 100);
  ledcWrite(motor2Channel, 100);
  // Choose direction
  digitalWrite(motor1Dir, HIGH);
  digitalWrite(motor2Dir, HIGH);

  delay(2000);
}
