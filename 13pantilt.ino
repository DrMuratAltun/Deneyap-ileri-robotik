#include "deneyap.h"
#include <ESP32Servo.h>
#define SERVOPIN1 D9
#define SERVOPIN2 D14
#define L1_pin A0
#define L2_pin A1
#define L3_pin A2
#define Pot_pin A3
int teta1min=0;
int teta1max=180;
int teta2min=0;
int teta2max=180;
int accAngleX=0;
int accAngleY=0;
int conavail=0;
int coef, valin1, valin2, valin3;
int pos1 = 0;
int pos2 = 0;
int clb1=0;
int clb2=0;
int clb3=0;
int i=0;
int n=10;
int32_t tot1=0.;
int32_t tot2=0.;
int32_t tot3=0.;
Servo myservo1, myservo2;
void setup()
{
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2);
}
void loop()
{
coef = analogRead(Pot_pin);
valin1 = 1023-analogRead(L1_pin);
valin2 = 1023-analogRead(L2_pin);
valin3 = 1023-analogRead(L3_pin);
if (i<n) {
i++;
}
tot1=int(((i-1)*tot1+valin1)/i);
tot2=int(((i-1)*tot2+valin2)/i);
tot3=int(((i-1)*tot3+valin3)/i);
pos1=90+(tot2-tot1)*((2048-coef)/2048.);
pos2=120+(0.5*(tot1+tot2)-tot3)*((2048-coef)/2048.);
myservo1.write(pos1);
myservo2.write(pos2);
delay(5);
}
