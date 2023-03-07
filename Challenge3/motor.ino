#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

// Motor R
int motor1Pin1 = 18; 
int motor1Pin2 = 15; 
int enable1Pin = 4; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle;

void setup() {
  nh.initNode();

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

  Serial.begin(57600);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop(){
  if (! nh.getParam("/input", &dutyCycle, 1)){
    dutyCycle = 0;
  }
  
  if (dutyCycle > 0.0 and dutyCycle <= 255.0){

    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, dutyCycle);

    Serial.println("Moving Forward"); 
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);   
  }

  else if (dutyCycle < 0 and dutyCycle >= -255){
    // Move DC motor backwards
    dutyCycle = dutyCycle * -1;
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel, dutyCycle);

    Serial.println("Moving Backwards");
    Serial.print("Backward with duty cycle: ");
    Serial.println(dutyCycle);   
  }

  else if (dutyCycle == 0){
    // Stop the DC motor
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);

    Serial.println("Motor stopped");
  }

  nh.spinOnce();
  delay(1000);
}

