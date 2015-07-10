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

int SO = 4;
int SC = 5;
int CS = 6;


#define AVG_TEMP_NUM 10
double avgTemp[AVG_TEMP_NUM];

LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
MAX6675 thermocouple(SC, CS, SO);
// make a cute degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup()
{
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
  double averageTemperature = 0;
  for(int i = AVG_TEMP_NUM-1; i > 0; i--){
    avgTemp[i] = avgTemp[i-1];
  }
  avgTemp[0] = thermocouple.readCelsius();
  for(int i = 0; i < AVG_TEMP_NUM; i++){
    averageTemperature += avgTemp[i];
  }
  averageTemperature /= AVG_TEMP_NUM;
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
