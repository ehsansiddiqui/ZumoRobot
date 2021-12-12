#include <Wire.h>
#include <ZumoShield.h>

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int default_position = 2500; // 1/2 * 5000(sensors 0-5)
const int INIT_SPEED = 100;
int pre_error = 0;
const int coff1 = 1;
const int coff2 = 3;

void setup()
{
  reflectanceSensors.init();// init reflectance sensors
  button.waitForButton(); //press the button to start up
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  reflectanceSensors.calibrate();
  motors.setSpeeds(0,0); // init speed(left,right)->speed(0,0)
  digitalWrite(13, LOW); // calibrate and speed initialization finished
  Serial.begin(9600);
}

void loop()
{
  unsigned int sensors[6];
 
  int position = reflectanceSensors.readLine(sensors[6]);
  Serial.println(position);//default_position is 2500
 
  int error = position - default_position;
  int speed_corr = coff1*error+coff2*(error-pre_error);//coff1 and coff2 is adaptive
  pre_error = error;
 
  int m1Speed = INIT_SPEED + speed_corr;
  int m2Speed = INIT_SPEED - speed_corr;
  motors.setSpeeds(m1Speed, m2Speed);//modify the speed to correct the error
}
