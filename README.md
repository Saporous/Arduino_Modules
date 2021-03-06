# Arduino_Modules
Code for applications of specific Arduino Modules implemented on either the Arduino Leonardo or Nano boards. All Arduino programming files included should contain all relevant files for standalone operation. Wiring diagrams for certain modules are included.

## ADC 
Demonstration of the Arduino's ADC capability on pin A7, works on Nano.

## Arduino-PID-Library
A library created by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
that implements PID using A0 to control A3.

## Digital humidity temperature sensor
An implementation of the DHT11 module that sends read humidity and temperature via serial.

## HC-16 LiquidCrystal_I2C For Arduino 1602LCD Display
A basic implementation of the SainSmart HC-16 breakout board. It uses I2C
to communicate with an Arduino board to display messages on a LCD display.
It currently works with a 20x4 character display, but may be modified to
work on a 16x2 character display. It displays "Hello World!" on two lines,
with a number counter on the bottom right corner.

## lcdthermocouple
A combined implementation of the HC-16 breakout board with the MAX6675
thermocouple high temperature sensor that displays the temperature read
via SPI from the Maxim breakout board on a LCD display via I2C.

## lcdthermocouplePID
An extension of the "lcdthermocouple" project that adds PID control from the
"Arduino-PID-Library" on the default pins A0 and A3.

## MAX6675-library
A library created for a variant of the Adafruit MAX6675 breakout board that 
communicates read values from a high-temperature thermocouple to an Arduino
board via SPI with S0 on D4, SC on D5, and CS on D6.

## strobeLight
A project utilizing a potentiometer, onboard LED, and Arduino interrupt
functionality to flash the onboard LED every time a falling edge is detected
on the interrupt pin 

## DSKDM Arduino
Varius modules used to interface with the DSKDM.

### DSKDM_KEYPAD
Relays pressed keys on the DSKDM keyboard to Serial output. TODO: handle
debouncing and I2C output.

### DSKDM_LED
Uses the Arduino to power 15 LEDs on the DSKDM that will be used to signal
various status messages to the user. TODO: Handle I2C input.
