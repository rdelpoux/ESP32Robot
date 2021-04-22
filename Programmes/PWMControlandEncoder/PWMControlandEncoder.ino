// PWM
int motor1Enable  = 32;
int motor1Dir     = 16;
int motor1Channel = 0;
int motor2Enable  = 33;
int motor2Dir     = 17;    
int motor2Channel = 1;

// Encoder
int S1A = 25;
int S1B = 27;
int S2A = 26;
int S2B = 14;

int posM1 = 0;
int posM2 = 0;

// Interruption Prototypes;
void IRAM_ATTR isr1A();
void IRAM_ATTR isr1B();
void IRAM_ATTR isr2A();
void IRAM_ATTR isr2B();


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

    
  // DC motor forward
  Serial.println("DC motor forward");
  // Define duty cycle
  ledcWrite(motor1Channel, 50);
  ledcWrite(motor2Channel, 50);
  // Choose direction
  digitalWrite(motor1Dir, LOW);
  digitalWrite(motor2Dir, HIGH);


  // interruption
  pinMode(S1A , INPUT_PULLUP);
  attachInterrupt(S1A , isr1A, CHANGE);

  pinMode(S1B , INPUT_PULLUP);
  attachInterrupt(S1B , isr1B, CHANGE);

  pinMode(S2A , INPUT_PULLUP);
  attachInterrupt(S2A , isr2A, CHANGE);

  pinMode(S2B , INPUT_PULLUP);
  attachInterrupt(S2B , isr2B, CHANGE);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Motor1 pos = ");
  Serial.print(posM1);  
  Serial.print("\tMotor2 pos = ");  
  Serial.println(posM2);

  delay(100);
}





void IRAM_ATTR isr1A() {
  //pos++;
  if (digitalRead(S1A) == digitalRead(S1B)) {
    posM1++;
  } else {
    posM1--;
  }
}
  

void IRAM_ATTR isr1B() {
  //pos++;
  if (digitalRead(S1A) != digitalRead(S1B)) {
    posM1++;
  } else {
    posM1--;
  }
}


void IRAM_ATTR isr2A() {
  //pos++;
  if (digitalRead(S2A) == digitalRead(S2B)) {
    posM2++;
  } else {
    posM2--;
  }
}
  

void IRAM_ATTR isr2B() {
  //pos++;
  if (digitalRead(S2A) != digitalRead(S2B)) {
    posM2++;
  } else {
    posM2--;
  }
}
