
#include <Servo.h>

Servo topServo;  // create servo object to control a servo
Servo botServo;

const float MAX_PADDLE_1 = 22.0;
const float MIN_PADDLE_1 = 7.0;
const float PADDLE_1_LENGTH = 5;
float paddle_1_distance = -1;

int topServoPin = 6;
int botServoPin = 5;

int trigPin = 13;
int echoPin = 12;
const float SPEED_OF_SOUND_INV = 29.14;


int laserPin = 9;

const float MAX_ANGLE_T = 16;
const float MAX_ANGLE_B = 30;

float tPos = 0.0; //Top Servo Current Angle
float bPos = 0.0; //Bottom Servo Current Angle

float tVel = 0.0;
float bVel = 0.0;

float maxDirSpeed = 0.01;

float backgroundColor = 255;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  randomSeed(analogRead(0));
  topServo.attach(topServoPin);  // attaches the servo on pin 9 to the servo object
  botServo.attach(botServoPin);

  //Random Initial Position
  tPos = random(MAX_ANGLE_T-5) + 5;
  bPos = random(MAX_ANGLE_B-5) + 5;

  //Zero Initial Position
  //tPos = 0;
  //bPos = 0;

  //Random Speed
  tVel = min(random(1000)/1000.0*maxDirSpeed - maxDirSpeed/2.0, 0.005);
  bVel = min(random(1000)/1000.0*maxDirSpeed - maxDirSpeed/2.0, 0.005);

  //Speed is zero setting
  //tVel = 0;
  //bVel = 0;

  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);
}

void loop() {

  //  tPos = 0;
  //  bPos = 0;
  //  topServo.write(tPos); 
  //  botServo.write(bPos);
  //  delay(1000);
  //  tPos = 0;
  //  bPos = MAX_ANGLE_B;
  //  topServo.write(tPos); 
  //  botServo.write(bPos);
  //  delay(1000);
  //  tPos = MAX_ANGLE_T;
  //  bPos = MAX_ANGLE_B;
  //  topServo.write(tPos); 
  //  botServo.write(bPos);
  //  delay(1000);
  //  tPos = MAX_ANGLE_T;
  //  bPos = 0;
  //  topServo.write(tPos); 
  //  botServo.write(bPos);
  //  delay(1000);


  topServo.write(tPos); 
  botServo.write(bPos);

  tPos = tPos + tVel;
  bPos = bPos + bVel;

  if (tPos <= 0) {
    tVel = -1 * tVel;
    tPos = 0; 
  } 
  else if (tPos >= MAX_ANGLE_T) {
    tVel = -1 * tVel;
    tPos = MAX_ANGLE_T;
  }

  if (bPos <= 0) {
    digitalWrite(trigPin, LOW);
    delay(2);
    digitalWrite(trigPin, HIGH);

    delay(10);
    digitalWrite(trigPin, LOW);
    float duration = pulseIn(echoPin, HIGH); // [microseconds]

    paddle_1_distance = duration/2 / SPEED_OF_SOUND_INV; //[m] Calculate the dsitance using the speed of sound

    float height = 40.0;
    float ballDist = height*tan(tPos/180*3.14) + 9.02;

    Serial.print(paddle_1_distance);
    Serial.print(",");
    Serial.print(ballDist);
    Serial.println("");

    if ( paddle_1_distance-1.2 < ballDist && ballDist < (paddle_1_distance + PADDLE_1_LENGTH + 1.2))
    {     
      bVel = min(-1.2 * bVel,0.037);
      tVel = 1.00 * tVel;
      bPos = 0; 
      Serial.println("HIT");
    } 
    else {

      tPos = MAX_ANGLE_T/2;
      bPos = MAX_ANGLE_B/2;
      tVel = 0;
      bVel = 0;
      Serial.println("MISSES");
      topServo.write(tPos); 
      botServo.write(bPos);
      delay(5000);

      tPos = MAX_ANGLE_T/2;
      bPos = MAX_ANGLE_B/2;


      randomSeed(analogRead(0));
      tVel = min(random(1000)/1000.0*maxDirSpeed - maxDirSpeed/2.0, 0.005);
      bVel = min(random(1000)/1000.0*maxDirSpeed - maxDirSpeed/2.0, 0.005);

    }

  } 
  else if (bPos >= MAX_ANGLE_B) {
    bVel = -1 * bVel;
    bPos = MAX_ANGLE_B;
  }


}



