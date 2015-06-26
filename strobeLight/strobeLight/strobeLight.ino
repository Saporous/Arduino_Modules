/*
  strobeLight - By Jeffrey Chen
  
*/
#if not (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328P__))
  #error Your board type is not supported!
#endif

#if (defined(__AVR_ATmega328P__))
  #define LED_PIN 13
  #define POT_PIN 3
  #define VCC_PIN 4
  #define INT_PIN 2
#endif
#if (defined(__AVR_ATmega32U4__))
  #define LED_PIN 13
  #define POT_PIN 0
  #define INT_PIN 3
#endif

float duration;
bool blinkFlag;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(INT_PIN, INPUT_PULLUP);
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
  attachInterrupt(0, blink, CHANGE);
}

void blink(){
  blinkFlag = 1;
}

// the loop function runs over and over again forever
void loop() {
  if(blinkFlag){
    blinkFlag = 0;
    digitalWrite(LED_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(duration);              // wait for a second
    digitalWrite(LED_PIN, HIGH);    // turn the LED off by making the voltage LOW
  }
  
  // get duration based upon pot input
  Serial.println(duration);
  duration = analogRead(POT_PIN)*5.0/1023.0;
  delay(500);
}
