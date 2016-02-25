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

  adcSetUp();
}

void loop() 
{

  Serial.println(ADCSRA);
  delay(1000);
  ADCSRA |= 0b01000000;
  Serial.println(ADCSRA);
 

 

  
  //Serial.println(x);

}

void adcSetUp()
{
  Serial.println(ADCSRB);
  ADCSRB |= 0b00000000;
  /*Turn on the ADC on the Atmega2560 to prepare for reads*/
  ADCSRA |= 0b10000000;
}

