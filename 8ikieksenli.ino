#include "deneyap.h"
#include <ESP32Servo.h>
#define SERVOPIN1 D14
#define SERVOPIN2 D9
Servo myservo1, myservo2;
int pos = 0;
void setup()
{
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2);
}
void loop()
{
for (pos = 0; pos <= 180; pos += 1) {
myservo1.write(pos);
myservo2.write(pos);
delay (10);
}
for (pos = 180; pos >= 0; pos -= 1) {
myservo1.write(pos);
myservo2.write(pos);
delay (10);
}
}
