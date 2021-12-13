#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
unsigned int sensors[6];
const int MAX_SPEED = 200;
const int TrigPin = 7;
const int EchoPin = 6;
float distance;

void setup()
{
  button.waitForButton();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  motors.setSpeeds(0,0);
  digitalWrite(13, LOW);
  button.waitForButton();
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.println("Ultrasonic sensor:"); 
}

void loop()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  distance = pulseIn(EchoPin, HIGH) / 58.00;
//  Serial.print(distance);
//  Serial.print("cm");
//  Serial.println(); 
  
  int m1Speed = MAX_SPEED;
  int m2Speed = MAX_SPEED; 
  if (distance < 10)
  {
    m1Speed = 0;
    m2Speed = 0;
  }

  motors.setSpeeds(m1Speed, m2Speed);
}
