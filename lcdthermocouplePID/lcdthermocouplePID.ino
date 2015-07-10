/*
** Example Arduino sketch for SainSmart I2C LCD2004 adapter for HD44780 LCD screens
** Readily found on eBay or http://www.sainsmart.com/ 
** The LCD2004 module appears to be identical to one marketed by YwRobot
**
** Address pins 0,1 & 2 are all permenantly tied high so the address is fixed at 0x27
**
** Written for and tested with Arduino 1.0
** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal 
**
** Edward Comer
** LICENSE: GNU General Public License, version 3 (GPL-3.0)
**
** NOTE: TEsted on Arduino NANO whose I2C pins are A4==SDA, A5==SCL
*/
#include <Wire.h>
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "max6675.h"
#include "PID_v1.h"

//#define I2C_ADDR    0x3F  // Define I2C Address where the PCF8574A is
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define PIN_INPUT 0
#define RELAY_PIN 6

int SO = 4;
int SC = 5;
int CS = 6;


#define AVG_TEMP_NUM 10
double avgTemp[AVG_TEMP_NUM];

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
MAX6675 thermocouple(SC, CS, SO);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=0, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;

void setup()
{
  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 100;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  Serial.begin(9600);
  digitalWrite(2, HIGH);
  lcd.begin (20,4);
  
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  thermocouple.readCelsius();
  lcd.setCursor(0,0);
  lcd.print("Getting average...");
  delay(1000);
  for(int i = 0; i < AVG_TEMP_NUM; i++){
    avgTemp[i] = thermocouple.readCelsius();
    delay(100);
  }
  lcd.clear();
}

void loop()
{
  // --------------- PID CODE ---------------
  double averageTemperature = 0;
  for(int i = AVG_TEMP_NUM-1; i > 0; i--){
    avgTemp[i] = avgTemp[i-1];
  }
  avgTemp[0] = thermocouple.readCelsius();
  for(int i = 0; i < AVG_TEMP_NUM; i++){
    averageTemperature += avgTemp[i];
  }
  averageTemperature /= AVG_TEMP_NUM;

  //Input = analogRead(PIN_INPUT);
  Input = 30;
  myPID.Compute();
  if (millis() - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime){
    lcd.setCursor(10, 0);
    lcd.print("HIGH");
    digitalWrite(RELAY_PIN, HIGH);
  }
  else{
    lcd.setCursor(10,0);
    lcd.print("LOW ");
    digitalWrite(RELAY_PIN, LOW);
  }


  // --------------- LCD CODE ---------------
//  lcd.print(thermocouple.readCelsius());
//  lcd.println(" C ");
  lcd.setCursor(0,0);
  lcd.print(averageTemperature);
  lcd.print(" C ");
  Serial.print(averageTemperature);
  Serial.println(" C ");
  
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print(averageTemperature*1.8 + 32);
  lcd.print(" F ");
  delay(500);
}
