#define	BLACK           0x00
#define	BLUE            0xE0
#define	RED             0x03
#define	GREEN           0x1C
#define	DGREEN           0x0C
#define YELLOW          0x1F
#define WHITE           0xFF
#define ALPHA           0xFE
#define	BROWN           0x32

  
#include "SSD1331.h"
#include <SPI.h>
#include <Wire.h>
#include "DSRTCLib.h"

#include <avr/power.h>
#include <avr/sleep.h>
SSD1331 display = SSD1331(0);
int ledPin =  13;
int INT_PIN = 3;
int int_number = 1;

DS1339 RTC = DS1339();

unsigned long lastReceivedTime=0;

unsigned long lastDisplayUpdate=0;
unsigned long displayUpdateInterval=1000;


unsigned long sleepTimer=0;
unsigned long sleepTimeout=5000;
int displayState=0;
int buttonReleased=1;

char notificationLine1[20]="Release 2.0.0";
char notificationLine2[20]="";

void setup(void) { // setup
  Wire.begin();
  display.begin();
  display.setFlip(1);
  display.setBrightness(3);
  RTC.start();
  display.fontColor(GREEN,BLACK);
  display.setFont(liberationSans_16ptFontInfo);
  display.setCursor(0,10);
  display.print("Hello");
  delay(2000);
  display.clearWindow(0,0,0,0);
}

void loop() {
  byte buttons = display.getButtons();
  if(buttonReleased && buttons){
  	if(displayState){
      notificationLine1[0]='\0';
      memcpy(notificationLine2,"  No notifications.",strlen("  No notifications."));
      displayNotifications();
  	}
    display.on();
    buttonReleased=0;
  }
  if(!buttonReleased && !(buttons&0x0F)){
    buttonReleased=1;
  }
  if(millis() > sleepTimer+sleepTimeout){
    if(displayState){
      displayState=0;
      display.off();
    }
  }
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char month;
  unsigned char day;
  unsigned int year;
  display.fontColor(BLACK,BLACK);
  RTC.readTime();
        second = RTC.getSeconds();
        minute = RTC.getMinutes();
        hour = RTC.getHours();        
        day = RTC.getDays();
        month = RTC.getMonths();        
        year = RTC.getYears();
        
  display.setFont(liberationSans_10ptFontInfo);    
  // Date      
  display.setCursor(0,10);
  display.fontColor(BLUE,BLACK);
  delay(10);
  display.print(month);
  display.print("/");
  display.print(day);
  display.print("/");
  display.print(year);
  
  // Time
  display.setCursor(0,30);
  display.fontColor(GREEN,BLACK);
  display.print(hour);
  display.print(":");
  
  if (RTC.getMinutes() < 10) // if minutes under 10
   {
     display.fontColor(YELLOW,BLACK);
     display.print("0");
     display.print(minute);
   }
   else 
   {
     display.fontColor(YELLOW,BLACK);
     display.print(minute);
   }
   
  display.fontColor(GREEN,BLACK); // set color
  
  display.print(":");
  
   if (RTC.getSeconds() < 10) // if seconds under 10
   {
     display.fontColor(RED,BLACK);
     display.print("0");
     display.print(second);
   }
   else 
   {
     display.fontColor(RED,BLACK);
     display.print(second);
     displayBattery();
     displayNotifications();
   }
}
void displayNotifications(){
  display.setFont(liberationSans_10ptFontInfo);
  display.setCursor(0,50);
  display.print(notificationLine1);
  for(int i=0;i<40;i++)display.write(' ');
  display.setCursor(0,50);
}
void displayBattery()
{
    const long InternalReferenceVoltage = 1100L;
  ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);
  delay(10);
  ADCSRA |= _BV( ADSC );
  while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
  int result = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L;
  //Serial.println(result);
  //if(result>440){//probably charging
  result=constrain(result-300,0,120);
  int x=72;
  int y=2;
  int height=8;
  int length=20;
  int amtActive=(result*length)/110;
  int red,green,blue;
  for(int i=0;i<length;i++){
    if(i<amtActive){
    red=63-((63/length)*i);
    green=((63/length)*i);
    blue=0;
    }else{
      red=32;
      green=32;
      blue=32;
    }
    display.drawLine(x+i,y,x+i,y+height,red,green,blue);
  }
}
