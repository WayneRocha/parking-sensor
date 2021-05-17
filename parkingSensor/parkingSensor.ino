const byte lightPin = 9;
const byte buzzerPin = 8;
const byte sensorTrigPin = 7;
const byte sensorEchoPin = 6;
const int buzzerFrequency = 200;
const int distanceToFire = 60;
bool carOnGarage;
float distancy;

void setup(){
  pinMode(lightPin, OUTPUT);
  pinMode(sensorTrigPin, OUTPUT);
  pinMode(sensorEchoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  measureDistance();
  if (carOnGarage){
    detectExit();
  } else {
    detectEntry();
  }
}
void detectEntry(){
  if (distancy < distanceToFire){
    lightOn();
    soundAlert();
    lightOff();
    carOnGarage = true;
  }
}
void detectExit(){
  if (distancy > distanceToFire){
    carOnGarage = false;
  }
}
void measureDistance(){
  digitalWrite(sensorTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
  float timeEcho = pulseIn(sensorEchoPin, HIGH);
  distancy = ((timeEcho * 340.90) / 2) / 10000;
}
void soundAlert(){
  for (byte i = 0; i <= 5; i++){
    tone(buzzerPin, buzzerFrequency);
    delay(250);
    noTone(buzzerPin);
    delay(250);
  }
}
void lightOn(){
  digitalWrite(lightPin, HIGH);
}
void lightOff(){
  digitalWrite(lightPin, LOW);
}
