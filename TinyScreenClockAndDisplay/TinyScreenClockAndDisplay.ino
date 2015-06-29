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
        
// weakday
      display.setFont(liberationSans_16ptFontInfo);
      display.fontColor(WHITE,BLACK);
      display.setCursor(0,40);
      Serial.println(weakday);
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
  else {
    display.print("ERROR");
  }

// Date      
  display.setFont(liberationSans_10ptFontInfo);
  display.fontColor(WHITE,BLACK);
  display.setCursor(1,1);
  // Months
  if (month == 1)
  {
    display.print("Jan");
  }
  else if (month == 2)
  {
    display.print("Feb");
  }
  else if (month == 3)
  {
    display.print("March");
  }
  else if (month == 4)
  {
    display.print("April");
  }
  else if (month == 5)
  {
    display.print("May");
  }
    else if (month == 6)
  {
    display.print("June");
  }
    else if (month == 7)
  {
    display.print("July");
  }
    else if (month == 8)
  {
    display.print("Augest");
  }
    else if (month == 9)
  {
    display.print("Sept");
  }
    else if (month == 10)
  {
    display.print("October");
  }
    else if (month == 11)
  {
    display.print("Nov");
  }
    else if (month == 12)
  {
    display.print("Dec");
  }
  display.print(" ");
  // Day
  if (day == 1)
  {
    display.print("1st");
  }
  else if (day == 2)
  {
    display.print("2nd");
  }
    else if (day == 3)
  {
    display.print("3rd");
  }
    else if ((day >=4)&&(day<=20)){
      display.print(day);
      display.print("th");
    }
    else if (day == 4)
  {
    display.print("4th");
  }
    else if (day == 5)
  {
    display.print("5th");
  }
    else if (day == 6)
  {
    display.print("6th");
  }
    else if (day == 7)
  {
    display.print("7th");
  }
    else if (day == 8)
  {
    display.print("8th");
  }
    else if (day == 9)
  {
    display.print("9th");
  }
    else if (day == 10)
  {
    display.print("10th");
  }
    else if (day == 11)
  {
    display.print("11th");
  }
    else if (day == 12)
  {
    display.print("12th");
  }
    else if (day == 13)
  {
    display.print("13th");
  }
    else if (day == 14)
  {
    display.print("14th");
  }
    else if (day == 15)
  {
    display.print("15th");
  }
    else if (day == 16)
  {
    display.print("16th");
  }
    else if (day == 17)
  {
    display.print("17th");
  }
    else if (day == 18)
  {
    display.print("18th");
  }
    else if (day == 19)
  {
    display.print("19th");
  }
    else if (day == 20)
  {
    display.print("20th");
  }
    else if (day == 21)
  {
    display.print("21st");
  }
    else if (day == 22)
  {
    display.print("22nd");
  }
    else if (day == 23)
  {
    display.print("23rd");
  }
    else if (day == 24)
  {
    display.print("24th");
  }
    else if (day == 25)
  {
    display.print("25th");
  }
    else if (day == 26)
  {
    display.print("26th");
  }
    else if (day == 27)
  {
    display.print("27th");
  }
    else if (day == 28)
  {
    display.print("28th");
  }
    else if (day == 29)
  {
    display.print("29th");
  }
    else if (day == 30)
  {
    display.print("30th");
  }
    else if (day == 31)
  {
    display.print("31st");
  }
// Time
  display.setFont(liberationSans_22ptFontInfo);
  display.setCursor(0,16);
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
  display.fontColor(WHITE,BLACK);
  display.print(" AM");
  }
  else {
    display.fontColor(WHITE,BLACK);
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
