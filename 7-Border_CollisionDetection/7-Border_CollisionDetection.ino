#include <Wire.h>
#include <ZumoShield.h>

#define threshold  1500 // microseconds
#define NUM_SENSORS 6

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

unsigned int sensor_values[NUM_SENSORS];

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
  sensors.read(sensor_values);
  distance = pulseIn(EchoPin, HIGH) / 58.00;
  if (sensor_values[0] < threshold)
  { // the leftmost sensor detect lines
    motors.setSpeeds(-200, -200);//revers
    delay(200);
    motors.setSpeeds(-200, 200);//turn right
    delay(200);
    motors.setSpeeds(200, 200);
  }
  else if (sensor_values[5] < threshold)
  { // the rightmost sensor detect lines
    motors.setSpeeds(-200, -200);//revers
    delay(200);
    motors.setSpeeds(-200, 200);//turn left
    delay(200);
    motors.setSpeeds(200, 200);
  }
  else
  {
    if(distance<3){ //distance not defined
      //another robot is in the front, less than 3cm
      //hit the robot
      motors.setSpeeds(400, 400);//max_speed forward to hit
    }
    else{
    motors.setSpeeds(200, 200);
    }
  }
} 
