#include <Wire.h>
#include <ZumoShield.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
unsigned int sensors[6];
int speedDifference = 0;
const int MAX_SPEED = 200;
const int TrigPin = 7;
const int EchoPin = 6;
float distance;

void setup()
{
  reflectanceSensors.init();
  button.waitForButton();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  reflectanceSensors.calibrate();
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
  
  int position = reflectanceSensors.readLine(sensors);
  int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;
  if (distance < 10)
  {
    m1Speed = 0;
    m2Speed = 0;
  }

  motors.setSpeeds(m1Speed, m2Speed);
}
