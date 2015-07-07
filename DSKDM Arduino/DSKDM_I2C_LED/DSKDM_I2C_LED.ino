#if not (defined(__AVR_ATmega328P__))
  #error Your board type is not supported!
#endif

#include <Wire.h>

#define I2C_ADDRESS 4

#if (defined(__AVR_ATmega328P__))
  #define LED0 2
  #define LED1 3
  #define LED2 4
  #define LED3 5
  #define LED4 6
  #define LED5 7
  #define LED6 8
  #define LED7 9
  #define LED8 10
  #define LED9 11
  #define LED10 12
  #define LED11 A0
  #define LED12 A1
  #define LED13 A2
  #define LED14 A3 
#endif

int LED[15] = {LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8,LED9,LED10,LED11,LED12,LED13,LED14};
int value = LOW;

void setup() {
  Wire.begin(I2C_ADDRESS)
  Serial.begin(9600);
  for(int i = 0; i < 15; i++){
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
   for(int k = 0; k < 15; k++){
    digitalWrite(LED[k], HIGH);
  }
  /*
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 15; j++){
      digitalWrite(LED[j], LOW);
    }
    digitalWrite(LED[i], HIGH);
    delay(500);
    Serial.print(LED[i]);
    Serial.print(" LED: ");
    Serial.println((String)LED[i]);
  }
  if(value == HIGH){
    value = LOW;
  }
  else value = HIGH;
  */
}
