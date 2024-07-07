#include "deneyap.h"
#include "lsm6dsm.h"
typedef struct struct_message {
float accel_x;
float accel_y;
float accel_z;
} struct_message;
LSM6DSM IMU;
struct_message imuData;
void setup()
{
Serial.begin(115200);
IMU.begin();
}
void loop()
{
imuData.accel_x = IMU.readFloatAccelX();
Serial.print("accel_x: ");
Serial.println(imuData.accel_x);
imuData.accel_y = IMU.readFloatAccelY();
Serial.print("accel_y: ");
Serial.println(imuData.accel_y);
imuData.accel_z = IMU.readFloatAccelZ();
Serial.print("accel_z: ");
Serial.println(imuData.accel_z);
delay(50);
}
