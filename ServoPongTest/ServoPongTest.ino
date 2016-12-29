
#include <Servo.h>

Servo topServo;  // create servo object to control a servo
Servo botServo;

int topServoPin = 6;
int botServoPin = 5;

int laserPin = 9;

const float MAX_ANGLE_T = 30;
const float MAX_ANGLE_B = 60;

float tPos = 0.0; //Top Servo Current Angle
float bPos = 0.0; //Bottom Servo Current Angle

float tVel = 0.0;
float bVel = 0.0;

float maxDirSpeed = 1;

float backgroundColor = 255;

void setup() {
  randomSeed(analogRead(0));
  topServo.attach(topServoPin);  // attaches the servo on pin 9 to the servo object
  botServo.attach(botServoPin);
  
  //Random Initial Position
  //tPos = random(MAX_ANGLE_T-5) + 5;
  //bPos = random(MAX_ANGLE_B-5) + 5;
  
  //Zero Initial Position
  tPos = 0;
  bPos = 0;
  
  //Random Speed
  tVel = random(maxDirSpeed*2) - maxDirSpeed/2.0;
  bVel = random(maxDirSpeed*2) - maxDirSpeed/2.0;
  
  //Speed is zero setting
  //tVel = 0;
  //bVel = 0;
  
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);
}

void loop() {

  topServo.write(tPos); 
  botServo.write(bPos);
  
  tPos = tPos + tVel;
  bPos = bPos + bVel;
  
  if (tPos <= 0) {
    tVel = -1 * tVel;
    tPos = 0; 
  } else if (tPos >= MAX_ANGLE_T) {
    tVel = -1 * tVel;
    tPos = MAX_ANGLE_T;
  }
  
  if (bPos <= 0) {
    bVel = -1 * bVel;
    bPos = 0; 
  } else if (bPos >= MAX_ANGLE_B) {
    bVel = -1 * bVel;
    bPos = MAX_ANGLE_B;
  }
  
  delay(50);                           // waits for the servo to get there
}
