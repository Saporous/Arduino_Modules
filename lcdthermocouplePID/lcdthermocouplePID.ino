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
#define PID_PIN_INPUT 0
#define PID_PIN_RELAY 6


int SO = 4;
int SC = 5;
int CS = 6;

int n = 1;
int avgTemp[10];



//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
MAX6675 thermocouple(SC, CS, SO);
// make a cute degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup()
{
  Serial.begin(9600);
  digitalWrite(2, HIGH);
  lcd.begin (20,4);

// populate temperature output array
  for(int i = 0; i < 10; i++){
    avgTemp[i] = thermocouple.readFahrenheit();
    delay(1);
  }
  
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
/*
  // PID Initialization
  windowStartTime = millis();
  //initialize the variables we're linked to
  Setpoint = 100;
  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  */
}

void loop()
{
/*
  // PID Stuff
  Input = thermocouple.readFahrenheit();
  myPID.Compute();

   turn the output pin on/off based on pid output


  if (millis() - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime) digitalWrite(PID_PIN_RELAY, HIGH);
  else digitalWrite(PID_PIN_RELAY, LOW);
*/
  for(int i = 0; i < 500; i++){
    avgTemp[i%10] = thermocouple.readFahrenheit();
    int temp = 0;
    for(int j = 0; j < 10; j++){
      temp += avgTemp[j];
    }
    temp /= 10;
    
    // LCD Update stuff
    lcd.setCursor(0,0);
    lcd.print(thermocouple.readCelsius());
    lcd.println(" C ");
    Serial.print(thermocouple.readCelsius());
    Serial.println(" C ");
    
    lcd.setCursor ( 0, 1 );        // go to the 2nd line
    lcd.print(temp);
    lcd.println(" F ");
  }
  delay(1);
}
