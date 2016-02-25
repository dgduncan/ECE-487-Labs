/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 3
 * 2/11/2016
 */

void setup() 
{
  /*Open Serial connection and display user prompt*/
  Serial.begin(9600);
  Serial.println("Input an 'a' to read the analog pin using analogRead().");
  Serial.println("Input a 'b' to read the analog pin using direct port manipulation.");

  /*Set up the analog to digital converter*/
  adcSetUp();
}

void loop() 
{
  

}

void adcSetUp()
{
  /*Set the ADC mux to use AVcc as the reference*/
  ADMUX |= 0b01000000;
  
  /*Turn on the ADC on the Atmega2560 to prepare for reads*/
  ADCSRA |= 0b10000000;
}

