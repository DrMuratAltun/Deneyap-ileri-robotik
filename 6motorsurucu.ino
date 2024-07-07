#include "deneyap.h"
#include "lsm6dsm.h"
#define MOT_ENA D12 // Motor hız kontrol pini
#define MOT_DIR1 D13 // Motor yon secme pin1
#define MOT_DIR2 D14 // Motor yon secme pin2
float ref_pos=90;
typedef struct struct_message {
float accel_x; //x yönünde ivme
float accel_y; //y yönünde ivme
float accel_z; //z yönünde ivme
} struct_message;
float angle_x=0.; //x açısı
float angle_y=0.; //y açısı46
int hiz=0;
LSM6DSM IMU; //Deneyap kart üzerinde bulunan IMU sensörü modeli
struct_message imuData;
void setup() {
IMU.begin();
pinMode(MOT_ENA, OUTPUT); // Motor hız kontrol pini cikis olarak ayarlandi
pinMode(MOT_DIR1, OUTPUT); // Motor yon secme pin1 cikis olarak ayarlandi
pinMode(MOT_DIR2, OUTPUT); // Motor yon secme pin2 cikis olarak ayarlandi
}
void loop() {
ref_pos=90; //servo motor başlangıç konumu 90 derece olarak ayarlanıyor.
imuData.accel_x = IMU.readFloatAccelX();
imuData.accel_y = IMU.readFloatAccelY();
imuData.accel_z = IMU.readFloatAccelZ();
//açı hesaplama denklemi (sqrt: karekök alma işlemi, pow: üs alma işlemi, PI: pi (π) sayısı)
angle_x = atan(imuData.accel_x / sqrt(pow(imuData.accel_y, 2) + pow(imuData.accel_z,
2)+0.001)) * 180 / PI;
hiz= abs(angle_x);
if(angle_x > 0) // Ileri yon
{
digitalWrite(MOT_DIR1, HIGH);
digitalWrite(MOT_DIR2, LOW);
}
else if(angle_x < 0) // Geri yon
{
digitalWrite(MOT_DIR1, LOW);
digitalWrite(MOT_DIR2, HIGH);
}
digitalWrite(MOT_ENA, LOW);
delay(100/hiz);
digitalWrite(MOT_ENA, HIGH);
delay(100/hiz);
}
