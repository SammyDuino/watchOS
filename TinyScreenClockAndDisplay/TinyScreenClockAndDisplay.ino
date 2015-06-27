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

int displayState=0;
int buttonReleased=0;
int countdown = 0;


void setup(void) {
  Wire.begin();
  display.begin();
  display.setFlip(1);
  display.setBrightness(5);
  Serial.begin(9600);
  RTC.start();
  startup();
  //Serial.println("Initialized");
  display.setCursor(0,30);
}

void loop() {
  byte buttons = display.getButtons();
  if(buttons != 0)
  {
    displayState = 1;
    display.on();
    countdown = 90;
    //Serial.println("Display on");
  	}
    if(buttons == 0){
      countdown=countdown-1;
    }
  if (countdown<=0){
  display.clearWindow(0,0,0,0);
  displayState=0;
  display.off();
  //Serial.println("Display off");
}
  //displayNotifications();
  displayBattery();
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char month;
  unsigned char day;
  unsigned int year;
  unsigned int weakday;
  char* dayOfWeekName[7];
  display.fontColor(BLACK,BLACK);
  RTC.readTime();
        second = RTC.getSeconds();
        minute = RTC.getMinutes();
        hour = RTC.getHours();        
        day = RTC.getDays();
        month = RTC.getMonths();        
        year = RTC.getYears();
        weakday = RTC.getDayOfWeek();
        
// Weekday
      display.setFont(liberationSans_10ptFontInfo);
      display.fontColor(BLUE,BLACK);
      display.setCursor(0,50);
    if (weakday == 1)
  {
      display.print("Sunday");
  }
  else if (weakday == 2)
  {
      display.print("Monday");
  }
  else if (weakday == 3)
  {
      display.print("Tuesday");
  }
   else if (weakday == 4)
  {
      display.print("Wednsday");
  }
     else if (weakday == 5)
  {
      display.print("Thursday");
  }
     else if (weakday == 6)
  {
      display.print("Friday");
  }
     else if (weakday == 7)
  {
      display.print("Saturday");
  }

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
  if (hour > 12) {
    hour = hour - 12;
  }
  display.print(hour);
  display.print(":");
  if (minute < 10) {
    display.print("0");
  }
  display.print(minute);
  if (hour > 12) {
  display.print(" AM");
  }
  else {
    display.print(" PM");
  }
}
void displayBattery()
{
    const long InternalReferenceVoltage = 1100L;
  ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);
  delay(10);
  ADCSRA |= _BV( ADSC );
  while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
  int result = (((InternalReferenceVoltage * 1024L) / ADC) + 5L) / 10L;
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
void startup()
{
  display.fontColor(GREEN,BLACK);
  display.setFont(liberationSans_16ptFontInfo);
  display.setCursor(0,10);
  display.print("Welcome");
  delay(2000);
  displayState = 1;
  display.on();
  countdown = 90;
  display.clearWindow(0,0,0,0);
}

