/*
Author:    Omer Ikram ul Haq
Date:      2014-05-18
Location:  Pakistan
Version:   ver 0.1 beta
Test with: Arduino Mega and Devention rx701
*/
/*ROS*/
#include <ros.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"
ros::NodeHandle  nh;
geometry_msgs::Twist carcontrol;
std_msgs::Float32 velocity;
std_msgs::Float32 steering;
ros::Publisher chatter("cmd_vel", &carcontrol);
/**/
#include "rc_rx.h"


#define dt 20         // [ms] Task time 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long t=0;

void setup()
{
//ros
nh.initNode();
nh.advertise(chatter);
// ros 
  Serial.begin(115200); // Initlizing serial port before calling init_rc_rx() function 
  init_rc_rx();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("velocity:");
  display.print(carcontrol.linear.x);
  display.print("\t");
  display.print("Steering");
  display.println(carcontrol.angular.z);
  display.display();
  delay(2000);
}

void loop()
{ 
  t = micros()/1000;
  
  read_rc_rx();        // CH1, CH2, CH3 and CH4 float variables will be calculated with this function is called

   carcontrol.linear.x=CH3;
   carcontrol.angular.z=CH2;
 


  Serial.print("velocity:");
  Serial.print( carcontrol.linear.x);
  Serial.print("\t");
  Serial.print("Steering");
  Serial.println(carcontrol.angular.z);
  
  chatter.publish(&carcontrol);
   nh.spinOnce();
  delay(1000);
  /*Serial.print(CH1);
  Serial.print("\t");
  Serial.print(CH2);
  Serial.print("\t");
  Serial.print(CH3);
  Serial.print("\t");
  Serial.print(CH4);
  Serial.print("\t");
  Serial.println(((micros()/1000)- (float)t)*100/dt);*/
  
  
  while (dt > (micros()/1000)- t){
  // do nothing
  }
  
  
}
