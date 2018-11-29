// GY-521 MPU6050 Raw Value example Develope by Commandrone
// www.commandronestore.com
#include "Wire.h"
#include "I2Cdev.h" 
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup() 
{
Wire.begin();
Serial.begin(38400);

Serial.println("Initialize MPU");
mpu.initialize();
Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
} 

void loop() //รับค่าและแสดงผลแกนต่างๆไปเรื่อยๆ
{
mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //คำสั่งรับค่าแกนต่างๆจาก Libraly
Serial.print("Axyz \t"); 
Serial.print(ax); Serial.print("\t"); 
Serial.print(ay); Serial.print("\t"); 
Serial.print(az); Serial.print("\t"); 
Serial.print("Gxyz \t"); 
Serial.print(gx); Serial.print("\t"); 
Serial.print(gy); Serial.print("\t"); 
Serial.println(gz); 

delay(100); //หน่วงเวลาซักหน่อย 
}
