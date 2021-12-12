#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
ZumoIMU imu;
char report[120];
const int MAX_SPEED = 400;

void setup()
{
  Wire.begin();
  imu.enableDefault();
  motors.setSpeeds(0,0);
  Serial.begin(9600);
}

void loop()
{
  imu.read();
  //print IMU(a,m,g)
  // experiment-1: accelerate forward
  // the speed is t^2, so the accelaration of forward direction is 2*t
  int speed_t;
  for(int t=0; t<20; t++){
    speed_t = t*t;
    motors.setSpeeds(speed_t,speed_t);
    snprintf_P(report, sizeof(report),
    PSTR("A: %6d %6d %6d    M: %6d %6d %6d    G: %6d %6d %6d"),
    imu.a.x, imu.a.y, imu.a.z,
    imu.m.x, imu.m.y, imu.m.z,
    imu.g.x, imu.g.y, imu.g.z);
    Serial.println(report);
    delay(100);
  }
  /*
  //experiment-2: rotate itself
  motors.setSpeeds(0,MAX_SPEED);
  snprintf_P(report, sizeof(report),
    PSTR("A: %6d %6d %6d    M: %6d %6d %6d    G: %6d %6d %6d"),
    imu.a.x, imu.a.y, imu.a.z,
    imu.m.x, imu.m.y, imu.m.z,
    imu.g.x, imu.g.y, imu.g.z);
    Serial.println(report);
    delay(100);
  */
  
}
