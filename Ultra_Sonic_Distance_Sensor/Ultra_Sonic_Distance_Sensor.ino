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
  // Play a little welcome song
  buzzer.play(">g32>>c32");

  // Initialize the reflectance sensors module
  reflectanceSensors.init();

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
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
  motors.setSpeeds(0,0);

  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  buzzer.play(">g32>>c32");

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());

  // using the ultrasonic sensor
  // 初始化串口通信及连接SR04的引脚
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  pinMode(EchoPin, INPUT);
  Serial.println("Ultrasonic sensor:"); 
}

void loop()
{
  //using the ultrasonic sensor to detect the distance
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  // 检测脉冲宽度，并计算出距离
  distance = pulseIn(EchoPin, HIGH) / 58.00;
//  Serial.print(distance);
//  Serial.print("cm");
//  Serial.println(); 
  
  int position = reflectanceSensors.readLine(sensors);
//  Serial.println(sensors[6]);

  int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;
  if (distance < 10)
  {
    m1Speed = 0;
    m2Speed = 0;
  }

  motors.setSpeeds(m1Speed, m2Speed);
}
