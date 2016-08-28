#define  BLACK           0x00
#define BLUE            0xE0
#define RED             0x03
#define GREEN           0x1C
#define DGREEN           0x0C
#define YELLOW          0x1F
#define WHITE           0xFF
#define ALPHA           0xFE
#define BROWN           0x32
// Define colors
  
#include "SSD1331.h"
#include <SPI.h>
#include <Wire.h>
#include "DSRTCLib.h"
// Define libraries

#include <avr/power.h>
#include <avr/sleep.h>
SSD1331 display = SSD1331(0);
int ledPin =  13;
int INT_PIN = 3;
int int_number = 1;
// Defins Pins

DS1339 RTC = DS1339();

int displayState=0;
int buttonReleased=0;
int countdown = 0;
int messages = 0;
// Defines integers being used

void setup(void) 
{
  start_coreservices();
  start_effects();
  display_battery();
}

void loop() 
{
  byte buttons = display.getButtons();

  if (buttons != 0)
  {
    displayState = 1;
    display.on();
    countdown = 90;
    messages++;
  }
  if (buttons == 0) 
  {
    countdown=countdown-1;
  }
  if (countdown<=0)
  {
    display.clearWindow(0,0,0,0);
    displayState = 0;
    display.off();
  }

  display.setFont(liberationSans_10ptFontInfo);
  display.fontColor(WHITE,BLACK);
  display.setCursor(0,40);
  if (messages == 0)
  {
    display.fontColor(YELLOW,BLACK);
    display.print("Sky beta 1");
  }
  if (messages == 10)
  {
    display.clearWindow(0,40,0,40);
    display.fontColor(BLUE,BLACK);
    display.print("More stuff coming soon!");
  }
  if (buttons == 2)
  {
    messages = 0;
    display.off();
    display.clearWindow(0,40,0,40);
    display.on();
  }
 
  displayBattery();
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char month;
  unsigned char day;
  unsigned int year;
  unsigned char hr;
  unsigned int weekday;
  char* dayOfWeekName[7];
  display.fontColor(BLACK,BLACK);
  RTC.readTime();
  second = RTC.getSeconds();
  minute = RTC.getMinutes();
  hour = RTC.getHours();        
  day = RTC.getDays();
  month = RTC.getMonths();        
  year = RTC.getYears();
  weekday = RTC.getDayOfWeek();
  hr = RTC.getHours();
  // Weekday
  if (messages > 40)
  {
  display.setFont(liberationSans_16ptFontInfo);
  display.fontColor(WHITE,BLACK);
  display.setCursor(0,40);
 switch (weekday) {
  case 0:
  display.print("Monday");
  break;
  case 1:
  display.print("Tuesday");
  break;
  case 2:
  display.print("Wednsday");
  break;
  case 3:
  display.print("Thursday");
  break;
  case 4:
  display.print("Friday");
  break;
  case 5:
  display.print("Saturday");
  break;
  case 6:
  display.print("Sunday");
  break;
  }
}
  // Date      
  display.setFont(liberationSans_10ptFontInfo);
  display.fontColor(WHITE,BLACK);
  display.setCursor(1,1);
  // Months
  switch (month) {
  case 1:
  display.print("Jan");
  break;
  case 2:
  display.print("Feb");
  break;
  case 3:
  display.print("March");
  break;
  case 4:
  display.print("April");
  break;
  case 5:
  display.print("May");
  break;
  case 6:
  display.print("June");
  break;
  case 7:
  display.print("July");
  break;
  case 8:
  display.print("Aug");
  break;
  case 9:
  display.print("Sept");
  break;
  case 10:
  display.print("Oct");
  break;
  case 11:
  display.print("Nov");
  break;
  case 12:
  display.print("Dec");
  break;
  }
  display.print(" ");
  // Day
  switch (day) {
  case 1:
  display.print("1st");
  break;
  case 2:
  display.print("2nd");
  break;
  case 3:
  display.print("3rd");
  break;
  case 21:
  display.print("21st");
  break;
  case 22:
  display.print("22nd");
  break;
  case 23:
  display.print("23rd");
  break;
  case 31:
  display.print("31st");
  break;
  }
  if ((day >=4) && (day<=20))
  {
  display.print(day);
  display.print("th");
  }
  if ((day >= 24) && (day <= 30))
  {
  display.print(day);
  display.print("th");
  }
// Time
  display.setFont(liberationSans_22ptFontInfo);
  display.setCursor(0,16);
  if (hour > 12) {
  hour = hour - 12;
  }
  display.print(hour);
  display.print(":");
  if (minute < 10)
  {
    display.print("0");
  }
  display.print(minute);

  display.setFont(liberationSans_16ptFontInfo);
  if (hr > 12)
  {
    display.print("PM");
  } else {
  display.print("AM");
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
  if (i<amtActive) 
  {
    red=63-((63/length)*i);
    green=((63/length)*i);
    blue=0;
    } 
    else {
      red=32;
      green=32;
      blue=32;
    }
    display.drawLine(x+i,y,x+i,y+height,red,green,blue);
  }
}
void start_coreservices()
{
  Wire.begin();
  display.begin();
  display.setFlip(1);
  display.setBrightness(5);
  Serial.begin(9600);
  RTC.start();
}
void display_battery()
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
  if (i<amtActive) 
  {
    red=63-((63/length)*i);
    green=((63/length)*i);
    blue=0;
  } else {
    red=32;
    green=32;
    blue=32;
    }
  display.drawLine(x+i,y,x+i,y+height,red,green,blue);
  }
}
void start_effects()
{
  display.fontColor(BLUE,BLACK);
  display.setFont(liberationSans_16ptFontInfo);
  display.setCursor(0,10);
  display.print("Sky");
  delay(2000);
  displayState = 1;
  display.on();
  countdown = 90;
  display.clearWindow(0,0,0,0);
}
