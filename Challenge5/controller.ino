#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

std_msgs::Float32 motorOutputData;
std_msgs::Float32 motorInputData;

// RIGHT Motor 
int motorRPin1 = 18; 
int motorRPin2 = 15; 
int enableRPin = 4; 
int encRA = 34;
int encRB = 36;

// LEFT Motor
int motorLPin1 = 13; 
int motorLPin2 = 14; 
int enableLPin = 2; 

int encLA = 39;
int encLB = 35;

// Setting RIGHT MOTOR PWM properties
const int freqR = 30000;
const int pwmChannelR = 0;
const int resolutionR = 8;
int dutyCycleR = 0;
// int dutyCycleRO = -1;

// Setting LEFT MOTOR PWM properties
const int freqL = 30000;
const int pwmChannelL = 1;
const int resolutionL = 8;
int dutyCycleL = 0;
// int dutyCycleLO = -1;

//Encoder
volatile long encoderCountR = 0;
int prevEnc = 0;
volatile long encoderCountL = 0;
unsigned long previousMillisR = 0;
unsigned long previousMillisL = 0;  

float rpsR;
const int sampleTime = 150;
const double rads_ticks = (2*3.1416)/753;


void callback(const std_msgs::Float32& motorInputData){
  dutyCycleR = motorInputData.data;
  if (dutyCycleR > 0){
    digitalWrite(motorRPin1, LOW);
    digitalWrite(motorRPin2, HIGH);
    ledcWrite(pwmChannelR, dutyCycleR);
  }
  else{
    digitalWrite(motorRPin1, HIGH);
    digitalWrite(motorRPin2, LOW);
    ledcWrite(pwmChannelR, dutyCycleR);
  }
}

ros::Publisher motorData_Pub("/motor_output", &motorOutputData);
ros::Subscriber<std_msgs::Float32>  motorData_Sub("/motor_input", &callback);

void setup() {
  nh.initNode();
  nh.advertise(motorData_Pub);
  nh.subscribe(motorData_Sub);
  // sets the Right Motor pins as outputs:
  pinMode(motorRPin1, OUTPUT);
  pinMode(motorRPin2, OUTPUT);
  pinMode(enableRPin, OUTPUT);

  // sets the Left Motor pins as outputs:
  pinMode(motorLPin1, OUTPUT);
  pinMode(motorLPin2, OUTPUT);
  pinMode(enableLPin, OUTPUT);

  //set the Encoder pins as inputs
  pinMode(encRA, INPUT_PULLUP);
  pinMode(encRB, INPUT_PULLUP);
  pinMode(encLA, INPUT_PULLUP);
  pinMode(encLB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encRA), encoderISRR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encLA), encoderISRL, CHANGE); 

  // configure LED PWM functionalitites
  ledcSetup(pwmChannelR, freqR, resolutionR);
  ledcSetup(pwmChannelL, freqL, resolutionL);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enableRPin, pwmChannelR);
  ledcAttachPin(enableLPin, pwmChannelL);

  Serial.begin(57600);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop(){
  unsigned long currentMillisR = millis();
  if (currentMillisR - previousMillisR >= sampleTime) {
    rpsR = ((encoderCountR-prevEnc)*rads_ticks*1000)/sampleTime; //radians per secondr
    prevEnc = encoderCountR;
    motorOutputData.data = rpsR;
  
    previousMillisR = currentMillisR;
    motorData_Pub.publish(&motorOutputData);
  }
  nh.spinOnce();
}

void encoderISRR(){
  if(digitalRead(encRA)==digitalRead(encRB)){
    encoderCountR++;
  }
  else{
    encoderCountR--;
  }
}

void encoderISRL(){
  if(digitalRead(encLA)==digitalRead(encLB)){
    encoderCountL++;
  }
  else{
    encoderCountL--;
  }
}