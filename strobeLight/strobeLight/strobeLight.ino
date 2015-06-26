/*
  strobeLight - By Jeffrey Chen
  
*/
#if not (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328__))
  #error Your board type is not supported!
#endif

#if (defined(__AVR_ATmega328__))
  #define LED_PIN 13
  #define POT_PIN 7
  #define INT_PIN 2
#endif
#if (defined(__AVR_ATmega32U4__))
  #define LED_PIN 13
  #define POT_PIN 0
  #define INT_PIN 3
#endif

int duration;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(0, blink, FALLING);
}

void blink(){
  // get duration based upon pot input
  duration = analogRead(POT_PIN)*6;
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(duration);              // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
  
}
