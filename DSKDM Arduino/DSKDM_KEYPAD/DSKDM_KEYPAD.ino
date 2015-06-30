#if not (defined(__AVR_ATmega328P__))
  #error Your board type is not supported!
#endif

#if (defined(__AVR_ATmega328P__))
  #define KEY0 2
  #define KEY1 3
  #define KEY2 4
  #define KEY3 5
  #define KEY4 6
  #define KEY5 7
  #define KEY6 8
  #define KEY7 9
  #define KEY8 10
  #define KEY9 11
  #define KEY10 12
#endif

#define NUMKEYS 11
int readFlag = 0;

int KEY[NUMKEYS] = {KEY0,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,KEY10};
int value = LOW;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < NUMKEYS; i++){
    pinMode(KEY[i], INPUT_PULLUP);
  }
}

void loop() {
  String temp = "";
  for(int i = 0; i < NUMKEYS; i++){
    if(!digitalRead(KEY[i])){
      readFlag = 1;
      temp += KEY[i];
      temp += " ";
    }
    delay(10);
  }
  if(readFlag) Serial.println(temp);
  else Serial.println("NO KEYS PRESSED");
  readFlag = 0;
  
}
