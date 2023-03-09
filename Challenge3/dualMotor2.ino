#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::String motorData;
ros::Publisher motorData_Pub("data", &motorData);


// RIGHT Motor 
int motorRPin1 = 18; 
int motorRPin2 = 15; 
int enableRPin = 4; 

// LEFT Motor B
int motorLPin1 = 13; 
int motorLPin2 = 14; 
int enableLPin = 2; 

// Setting RIGHT MOTOR PWM properties
const int freqR = 30000;
const int pwmChannelR = 0;
const int resolutionR = 8;
int dutyCycleR;
int dutyCycleRO = -1;

// Setting LEFT MOTOR PWM properties
const int freqL = 30000;
const int pwmChannelL = 1;
const int resolutionL = 8;
int dutyCycleL;
int dutyCycleLO = -1;

void setup() {
  nh.initNode();
  nh.advertise(motorData_Pub);

  // sets the pins as outputs:
  pinMode(motorRPin1, OUTPUT);
  pinMode(motorRPin2, OUTPUT);
  pinMode(enableRPin, OUTPUT);

  pinMode(motorLPin1, OUTPUT);
  pinMode(motorLPin2, OUTPUT);
  pinMode(enableLPin, OUTPUT);
  
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
  if (! nh.getParam("/rm", &dutyCycleR, 1)){
    dutyCycleR = 0;
  }
  if (! nh.getParam("/lm", &dutyCycleL, 1)){
    dutyCycleL = 0;
  }

  if (dutyCycleR != dutyCycleRO){
    motor(dutyCycleR, pwmChannelR, motorRPin1, motorRPin2, 1);
    dutyCycleRO == dutyCycleR;
  }
  if (dutyCycleL != dutyCycleLO){
    motor(dutyCycleL, pwmChannelL, motorLPin1, motorLPin2, 2);
    dutyCycleLO == dutyCycleL;
  }
  // motor(dutyCycleR, pwmChannelR, motorRPin1, motorRPin2, 1);
  // motor(dutyCycleL, pwmChannelL, motorLPin1, motorLPin2, 2);
  
  motorData_Pub.publish(&motorData);
  nh.spinOnce();
  // delay(1000);//Intentar reducirlo o quitarlo...
}

void motor(int dutyCycle, int pwmChannel, int motorPin1, int motorPin2, int sw){
  if (sw == 1){
    if (dutyCycle > 0.0 and dutyCycle <= 255.0){
      // Move the left DC motor forward
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(pwmChannel, dutyCycle);

      motorData.data = "Right Motor Forward";
        
    }

    else if (dutyCycle < 0 and dutyCycle >= -255){
      // Move DC motor backwards
      dutyCycle = dutyCycle * -1;
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW); 
      ledcWrite(pwmChannel, dutyCycle);

      motorData.data = "Right Motor Backwards";
    }

    else if (dutyCycle == 0){
      // Stop the DC motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);

      motorData.data = "Right Motor Stopped";
    }
    else{
      sw = 0;
    }
  }
  else if (sw == 2){
    if (dutyCycle > 0.0 and dutyCycle <= 255.0){
      // Move the left DC motor forward
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      ledcWrite(pwmChannel, dutyCycle);
      
      motorData.data = "Left Motor Forward";   
    }

    else if (dutyCycle < 0 and dutyCycle >= -255){
      // Move DC motor backwards
      dutyCycle = dutyCycle * -1;
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH); 
      ledcWrite(pwmChannel, dutyCycle);

      motorData.data = "Left Motor Backward";
    }

    else if (dutyCycle == 0){
      // Stop the DC motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);

      motorData.data = ("Left Motor stopped");
    }
    else{
      sw = 0;
    }  
  }
}

