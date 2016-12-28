int trigPin = 13;
int echoPin = 12;

const float SPEED_OF_SOUND_INV = 29.14; //[us/cm] microsecond per centimeter


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly: 

  //Trigger a Pulse
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);

  delay(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH); // [microseconds]

  float distance = duration/2 / SPEED_OF_SOUND_INV; //[m] Calculate the dsitance using the speed of sound

  if (distance <= 1000) {
    Serial.print(distance);
    Serial.println("");
  }
  
  delay(50);
}

