#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
//AD0 low = 0x68; //(default for InvenSense evaluation board)
//AD0 high = 0x69;
//MPU6050 accelgyro;
MPU6050 accelgyroIC1(0x68);
MPU6050 accelgyroIC2(0x69);

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;

int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;


void setup() {
// join I2C bus (I2Cdev library doesn't do this automatically)
Wire.begin();
Serial.begin(38400);
Serial.println("Initializing I2C devices...");
//accelgyro.initialize();
accelgyroIC1.initialize();
accelgyroIC2.initialize();

// verify connection
Serial.println("Testing device connections...");
}

void loop() {
// read raw accel/gyro measurements from device
accelgyroIC1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
accelgyroIC2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
// these methods (and a few others) are also available
//accelgyro.getAcceleration(&ax, &ay, &az);
//accelgyro.getRotation(&gx, &gy, &gz);a

// display tab-separated accel/gyro x/y/z values
//*
Serial.print("MPU1:\t");
Serial.print(ax1); Serial.print("\t");
Serial.print(ay1); Serial.print("\t");
Serial.print(az1); Serial.print("\t");
Serial.print(gx1); Serial.print("\t");
Serial.print(gy1); Serial.print("\t");
Serial.println(gz1);
//*/

//*
// display tab-separated accel/gyro x/y/z values
Serial.print("MPU2:\t");
Serial.print(ax2); Serial.print("\t");
Serial.print(ay2); Serial.print("\t");
Serial.print(az2); Serial.print("\t");
Serial.print(gx2); Serial.print("\t");
Serial.print(gy2); Serial.print("\t");
Serial.println(gz2);
//*/
}
