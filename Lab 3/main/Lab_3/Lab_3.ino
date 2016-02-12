#include <avr/wdt.h>
#include <SegmentDisplay.h>

/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 3
 * 2/11/2016
 */

/*Declare and Initalize the SegmentDisplay class with the appropriate pins*/
SegmentDisplay segmentDisplay(2, 3, 4, 5, 6, 7, 8, 9);
/*************************************************************************/


int wdtResetCount;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Please type in number to display on 7-Segment");

  segmentDisplay.displayDecimalPoint();

  watchdogTimerSetup();

}

void loop() 
{

  /*Variable Initialization and first reading*/
  char userInput = checkSerial();
  /*******************************************/ 

}

void watchdogTimerSetup()
{

  wdtResetCount = 0;

  cli();

  MCUSR = 0; 

  WDTCSR |= 0b00011000;

  WDTCSR =  0b01000000 | 0b000110;

  sei();
  
}

ISR(WDT_vect) // watchdog timer interrupt service routine
{
 wdtResetCount+=1;


 if(wdtResetCount != 2)
 {
    wdt_reset(); // start timer again (still in interrupt-only mode)
 }

 else
 {
  MCUSR = 0;                          // reset flags

                                       // Put timer in reset-only mode:
   WDTCSR |= 0b00011000;               // Enter config mode.
   WDTCSR =  0b00001000 | 0b000000;
 }
}

char checkSerial()
{
  /*Initialized character y */
  char firstCharacter;
  /*************************/

  if(Serial.available())
  {
    /*Read first byte of the stream*/
    firstCharacter = Serial.read();
    /*******************************/

    /*Enters method to clear serial input stream*/
    clearSerialInput();
    /********************************************/

    wdt_reset();
    
    if(firstCharacter!= '\r')
    {
      Serial.println(firstCharacter);
      int x = firstCharacter - '0';
      segmentDisplay.displayHex(x);
    }

    /*Return character containing first byte of the stream*/
    return firstCharacter;
    /****************************************************/
  }
}

void clearSerialInput()
{
  /*While loop to clear all data in the serial input stream*/
  while(Serial.available())
  {
    Serial.read();
  }
  /*********************************************************/

  /*Apparently there is some delay in clearing the data, so delay prevents a double run through of the code*/
  delay(100);
  /*********************************************************************************************************/
}

