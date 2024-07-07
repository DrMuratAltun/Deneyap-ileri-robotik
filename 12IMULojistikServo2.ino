#include "deneyap.h"
#include <ESP32Servo.h>
#include "lsm6dsm.h"
#define SERVOPIN1 D14
#define SERVOPIN2 D9
#define X_pin A0
#define Y_pin A1
int X_Val, Y_Val;
int dly = 5;
// writeMicroseconds fonksiyonuna girilen değer normal açı değerinden çok yüksek olduğundan stp değeri 10 kat fazla girilir.
int stp = 10;
int X_jys=0, Y_jys=0;
int teta1min=0;
int teta1max=3000; // 180 dereceye karşılık gelmektedir.
int teta2min=0;
int teta2max=3000;
float accAngleX=0.;
float accAngleY=0.;
typedef struct struct_message {
float accel_x;
float accel_y;
float accel_z;
} struct_message;
LSM6DSM IMU;
struct_message imuData;
Servo myservo1;
Servo myservo2;
int pos1 = 1500; // 90 dereceye karşılık gelmektedir.
int pos2 = 1500;
void setup()
{
IMU.begin();
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2);
pinMode(BUILTIN_KEY, INPUT);
pinMode(X_pin, INPUT);
pinMode(Y_pin, INPUT);
pinMode(LEDR, OUTPUT);
pinMode(LEDG, OUTPUT);
pinMode(LEDB, OUTPUT);
digitalWrite(LEDR, LOW);
digitalWrite(LEDG, HIGH);
digitalWrite(LEDB, HIGH);
}
void loop()
{
X_Val = analogRead(X_pin);
Y_Val = analogRead(Y_pin);
uint8_t buttonState = digitalRead(BUILTIN_KEY);
if(buttonState == BUTTON_PRESSED)
{
if (dly==5) {
dly=10;
digitalWrite(LEDR, HIGH);
digitalWrite(LEDG, LOW);
}
else {
if(dly==10) {
dly=20;
digitalWrite(LEDG, HIGH);
digitalWrite(LEDB, LOW);
}
else if (dly==20) {
dly=5;
digitalWrite(LEDR, LOW);
digitalWrite(LEDB, HIGH);
}
}
delay(300);
}
if (X_Val<1000 && pos1>teta1min) X_jys-=stp;
if (X_Val>3000 && pos1<teta1max) X_jys+=stp;
if (Y_Val<1000 && pos2>teta2min) Y_jys-=stp;
if (Y_Val>3000 && pos2<teta2max) Y_jys+=stp;
imuData.accel_x = IMU.readFloatAccelX();
imuData.accel_y = IMU.readFloatAccelY();
imuData.accel_z = IMU.readFloatAccelZ();
accAngleX = atan(imuData.accel_x / sqrt(pow(imuData.accel_y, 2) +
pow(imuData.accel_z, 2)+0.001)) * 180 / PI;
accAngleY = atan(-1 * imuData.accel_y / sqrt(pow(imuData.accel_x, 2) +
pow(imuData.accel_z, 2)+0.001)) * 180 / PI;
// writeMicroseconds fonksiyonu için revize edildi.
pos1=1500+int(accAngleX*3000./180.)+X_jys;
pos2=1500+int(accAngleY*3000./180.)+Y_jys;
myservo1.write(pos1);
myservo2.write(pos2);
delay(dly);
}