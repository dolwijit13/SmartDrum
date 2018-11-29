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

int cnt1;
int cnt2;
int lastLeftOrRight1;
int lastLeftOrRight2;

#define encoderOutA 13 // CLK pin of Rotary Enocoder
#define encoderOutB 12 // DT pin of Rotary Enocoder

int counter = 15; 
int presentState;
int previousState; 

void setup()
{
  pinMode (encoderOutA,INPUT);
  pinMode (encoderOutB,INPUT);
  previousState = digitalRead(encoderOutA);   // Get current state of the encoderOutA
  
  cnt1=0;
  lastLeftOrRight1=0;
  cnt2=0;
  lastLeftOrRight2=0;
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
    int state=0;
    if(counter>20)
    {
      state=2;
    }
    else if(counter>10)
    {
      state=1;
    }
    else
    {
      state=0;
    }
    
    if ((WiFiMulti.run() == WL_CONNECTED)) 
    {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    USE_SERIAL.print("access http://192.168.43.74:5000/?key=");
    if(mode==0)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=000"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=001"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=002"); //HTTP
      }
    }
    else if(mode==1)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=100"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=101"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=102"); //HTTP
      }
    }
    else if(mode==2)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=200"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=201"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=202"); //HTTP
      }
    }
    else if(mode==3)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=300"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=301"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=302"); //HTTP
      }
    }
    else if(mode==4)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=400"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=401"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=402"); //HTTP
      }
    }
    else if(mode==5)
    {
      if(state==0)
      {
          http.begin("http://192.168.43.74:5000/?key=500"); //HTTP
      }
      else if(state==1)
      {
        http.begin("http://192.168.43.74:5000/?key=501"); //HTTP
      }
      else if(state==2)
      {
        http.begin("http://192.168.43.74:5000/?key=502"); //HTTP
      }
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
    presentState = digitalRead(encoderOutA); 
    if (presentState != previousState)
    {     
      if (digitalRead(encoderOutB) != presentState) 
      { 
        counter++;
      } 
      else 
      {
         counter--;
      }
      if(counter<0)
      {
        counter+=30;
      }
      else if(counter>=30)
      {
        counter-=30;
      }
      Serial.print(counter);
    } 
    previousState = presentState; // Replace previous state of the encoderOutA with the current state
    
    cnt1++;
    cnt2++;
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
   
    if(cnt1%delayTime == 0)
    {
      // display tab-separated accel/gyro x/y/z values
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
    
    ///LEFT
    ///up&down
    if(gy1<=-30000 && cnt1>=delayTime)
    {
      //gy->az->gy
        Serial.print(gy1);
        play(1);
        cnt1=0;
        lastLeftOrRight1=0;
    }

    //right
    //gz->gx
    if(gx1<=-30000 && cnt1>=delayTime)
    {
        if(lastLeftOrRight1==1)
        {
          lastLeftOrRight1=0;
        }
        else
        {
          Serial.print(gx1);
          play(2);
          lastLeftOrRight1=-1;
        }
        cnt1=0;
    }

    //left
    if(gx1>=30000 && cnt1>=delayTime)
    {
        if(lastLeftOrRight1==-1)
        {
          lastLeftOrRight1=0;
        }
        else
        {
          Serial.print(gx1);
          play(0);
          lastLeftOrRight1=1;
        }
        cnt1=0;
    }

    ///RIGHT
    ///up&down
    if(gy2<=-30000 && cnt2>=delayTime)
    {
      //gy->az->gy
        Serial.print(gy2);
        play(4);
        cnt2=0;
        lastLeftOrRight2=0;
    }

    //right
    //gz->gx
    if(gx2<=-30000 && cnt2>=delayTime)
    {
        if(lastLeftOrRight2==1)
        {
          lastLeftOrRight2=0;
        }
        else
        {
          Serial.print(gx2);
          play(5);
          lastLeftOrRight2=-1;
        }
        cnt2=0;
    }

    //left
    if(gx2>=30000 && cnt2>=delayTime)
    {
        if(lastLeftOrRight2==-1)
        {
          lastLeftOrRight2=0;
        }
        else
        {
          Serial.print(gx2);
          play(3);
          lastLeftOrRight2=1;
        }
        cnt2=0;
    }
    }
}
