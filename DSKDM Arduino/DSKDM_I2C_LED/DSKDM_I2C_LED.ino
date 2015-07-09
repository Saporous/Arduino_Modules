#if not (defined(__AVR_ATmega328P__))
  #error Your board type is not supported!
#endif

#include <Wire.h>

#define I2C_ADDRESS 4
#define LED_COUNT 15

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

int LED[LED_COUNT] = {LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8,LED9,LED10,LED11,LED12,LED13,LED14};
int value = LOW;

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  for(int i = 0; i < 15; i++){
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  delay(10);
}

void receiveEvent(int numBytesReceived){
  byte temp = 0;
  int counter = 0;
  // loop through the entire message
  while(Wire.available()){
    temp = Wire.read();
    temp = (int)temp;
    counter++;
    counter = counter % LED_COUNT;
      temp -= 48;
      if(temp == 1){
        digitalWrite(LED[counter], HIGH);
        Serial.print(counter);
        Serial.println(" Set to HIGH");
      }
      else if(temp == 0){
        digitalWrite(LED[counter], LOW);
        Serial.print(counter);
        Serial.println(" Set to LOW");
      }
      else
        Serial.println("UNKNOWN BUTTON SENT");
  }
}


