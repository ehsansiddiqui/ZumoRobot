#include <Wire.h>
#include <ZumoShield.h>

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int default_position = 2500; // 1/2 * 5000(sensors 0-5)
const int INIT_SPEED = 300;
int pre_error = 0;
const int coff1 = 1;
const int coff2 = 3;

void setup()
{
  reflectanceSensors.init();// init reflectance sensors
  button.waitForButton(); //press the button to start up
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  int i;
  //sensor calibration
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0); // init speed(left,right)->speed(0,0)
  digitalWrite(13, LOW); // calibrate and speed initialization finished
  button.waitForButton();
  Serial.begin(9600);
}

void loop()
{
  unsigned int sensors[6];
 
  int position = reflectanceSensors.readLine(sensors);
  Serial.println(position);//default_position is 2500
 
  int error = position - default_position;
  int speed_corr = coff1*error+coff2*(error-pre_error);//coff1 and coff2 is adaptive
  pre_error = error;
 
  int m1Speed = INIT_SPEED + speed_corr;
  int m2Speed = INIT_SPEED - speed_corr;
  motors.setSpeeds(m1Speed, m2Speed);//modify the speed to correct the error
}
