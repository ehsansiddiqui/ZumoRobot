#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int INIT_SPEED = 200;
const int MAX_SPEED = 1000;
const int MIN_SPEED = 0;
const int DIFF_SPEED = 200;

void setup()
{
  button.waitForButton(); //press the button to start up
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  motors.setSpeeds(0,0); // calibration mode
  digitalWrite(13, LOW); //prepared
}

void loop()
{
  unsigned int sensors[6];
  /*
  // circle: different speed on the left and right wheel continously
  int m1Speed = INIT_SPEED + DIFF_SPEED;
  int m2Speed = INIT_SPEED;
  motors.setSpeeds(m1Speed, m2Speed);
  */
  //square
  for(int i=0; i<4; i++){
    motors.setSpeeds(INIT_SPEED,INIT_SPEED);
    delay(4000);
    if(i==3) {break;}
    motors.setSpeeds(MAX_SPEED, MIN_SPEED);
    delay(500);
  }
}
