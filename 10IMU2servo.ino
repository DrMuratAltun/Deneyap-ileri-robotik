#include "deneyap.h"
#include <ESP32Servo.h>
#include "lsm6dsm.h"
#define SERVOPIN1 D14
#define SERVOPIN2 D9
typedef struct struct_message {
float accel_x;
float accel_y;
float accel_z;
} struct_message;
LSM6DSM IMU;
struct_message imuData;
Servo myservo1;
Servo myservo2;
float accAngleX=0.;
float accAngleY=0.;
int pos1 = 90;
int pos2 = 90;
void setup()
{
IMU.begin();
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2);
}
void loop()
{
imuData.accel_x = IMU.readFloatAccelX();
imuData.accel_y = IMU.readFloatAccelY();
imuData.accel_z = IMU.readFloatAccelZ();
accAngleX = atan(imuData.accel_x / sqrt(pow(imuData.accel_y, 2) +
pow(imuData.accel_z, 2)+0.001)) * 180 / PI;
accAngleY = atan(-1 * imuData.accel_y / sqrt(pow(imuData.accel_x, 2) +
pow(imuData.accel_z, 2)+0.001)) * 180 / PI;
pos1=90+int(accAngleX);
pos2=90+int(accAngleY);
myservo1.write(pos1);
myservo2.write(pos2);
delay(10);
}
