//TMP36 Pin Variables
int sensorPin = 7; //Says we are working with a sensor in analog pin 0
/*
* setup() - this function runs once when you turn your Arduino on
* We initialize the serial connection with the computer
*/
void setup()
{
 Serial.begin(9600); //Start the serial connection with the computer
 //to view the result open the serial monitor 
}
void loop() // run over and over againx
{
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin); 
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; // print out the voltage to the serial port
  Serial.print(voltage); 
  Serial.println(" volts");
  delay(1000); //waiting a second
}
