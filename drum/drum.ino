// GY-521 MPU6050 Raw Value example Develope by Commandrone
// www.commandronestore.com
#include "Wire.h"
#include "I2Cdev.h" 
#include "MPU6050.h"

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;


MPU6050 accelgyroIC1(0x68);
MPU6050 accelgyroIC2(0x69);
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;

int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
int cnt;
int lastLeftOrRight;
void setup()
{
  cnt=0;
  lastLeftOrRight=0;
  Wire.begin();
  accelgyroIC1.initialize();
  accelgyroIC2.initialize();
  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("bump", "11111111");

}

void play(int mode)
{
    if ((WiFiMulti.run() == WL_CONNECTED)) 
    {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    USE_SERIAL.print("access http://192.168.43.74:5000/?key=");
    if(mode==0)
    {
      http.begin("http://192.168.43.74:5000/?key=000"); //HTTP
    }
    else if(mode==1 || mode==2)
    {
      http.begin("http://192.168.43.74:5000/?key=100"); //HTTP
    }
    else if(mode==3)
    {
      http.begin("http://192.168.43.74:5000/?key=200"); //HTTP
    }
    else
    {
      http.begin("http://192.168.43.74:5000/?key=300"); //HTTP
    }

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  
      http.end();
    }
}

void loop() //รับค่าและแสดงผลแกนต่างๆไปเรื่อยๆ
{
    cnt++;
    int delayTime=180;
    accelgyroIC1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
    accelgyroIC2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
    if(ax1==0 && ay1==0 && az1==0 && gx1==0 && gy1==0 && gz1==0)
    {
      Serial.print("ERROR!!!??? \n");
      delay(1000);
    }
    else
    {
   
    if(cnt%delayTime == 0)
    {
      Serial.print("MPU1:\t");
Serial.print(ax1); Serial.print("\t");
Serial.print(ay1); Serial.print("\t");
Serial.print(az1); Serial.print("\t");
Serial.print(gx1); Serial.print("\t");
Serial.print(gy1); Serial.print("\t");
Serial.println(gz1);


// display tab-separated accel/gyro x/y/z values
Serial.print("MPU2:\t");
Serial.print(ax2); Serial.print("\t");
Serial.print(ay2); Serial.print("\t");
Serial.print(az2); Serial.print("\t");
Serial.print(gx2); Serial.print("\t");
Serial.print(gy2); Serial.print("\t");
Serial.println(gz2);
    }
    ///up&down
    if(az1>=2000 && cnt>=delayTime)
    {
      //gy->az
        Serial.print(az1);
        play(1);
        cnt=0;
        lastLeftOrRight=0;
    }
    //gz->gx
    if(gx1<=-20000 && cnt>=delayTime)
    {
        if(lastLeftOrRight==1)
        {
          lastLeftOrRight=0;
        }
        else
        {
          Serial.print(gx1);
          play(0);
          lastLeftOrRight=-1;
        }
        cnt=0;
    }
    if(gx1>=20000 && cnt>=delayTime)
    {
        if(lastLeftOrRight==-1)
        {
          lastLeftOrRight=0;
        }
        else
        {
          Serial.print(gx1);
          play(2);
          lastLeftOrRight=1;
        }
        cnt=0;
    }

    if(az2>=2000 && cnt>=delayTime)
    {
      //gy->az
        Serial.print(az2);
        play(3);
        cnt=0;
        lastLeftOrRight=0;
    }
    //gz->gx
    if(gx2<=-20000 && cnt>=delayTime)
    {
        if(lastLeftOrRight==1)
        {
          lastLeftOrRight=0;
        }
        else
        {
          Serial.print(gx2);
          play(3);
          lastLeftOrRight=-1;
        }
        cnt=0;
    }
    if(gx2>=20000 && cnt>=delayTime)
    {
        if(lastLeftOrRight==-1)
        {
          lastLeftOrRight=0;
        }
        else
        {
          Serial.print(gx2);
          play(3);
          lastLeftOrRight=1;
        }
        cnt=0;
    }
    }
}
