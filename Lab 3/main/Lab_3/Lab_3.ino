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
  checkSerial();
  /*******************************************/

}

boolean checkSerial()
{
  delay(50);

  /*Checks if there are more than 3 characters in the stream*/
  if(Serial.available() > 3)
  {
    /*Notifies user that they messed up*/
    Serial.println("Can not display that");
    /**********************************/

    segmentDisplay.displayHex(-1);

    resetProcedure();

    /*Return flag that tells if integer was displayed*/
    return false;
    /*************************************************/
  }
  /**********************************************************/

  else if (Serial.available() > 2)
  {
    
    /*Read first and second byte of the stream*/
    int firstInt = Serial.read() - '0';
    int secondInt = Serial.read() - '0';
    /*******************************/

    if(checkIfNumbers(firstInt, secondInt))
    {
      resetProcedure();
      
      segmentDisplay.displayHex(recombineNumber(firstInt, secondInt));

      return true;
    }

    else
    {
      resetProcedure();
      
      return false;
    }
  }

  else if(Serial.available() > 1)
  {
    int firstInt = Serial.read() - '0';
      
    if(firstInt >= 0 && firstInt <= 9)
    {
      resetProcedure();

      segmentDisplay.displayHex(firstInt);
      
      return true; 
    }
    else
    {
      resetProcedure();
      
      return false;
    }
  }
}  

boolean checkIfNumbers(int first, int second)
{
  if((first >= 0 && first <= 9) && (second >= 0 && second <= 9))
    {
      return true;
    }
    else
    {
      Serial.println("That's not an Integer");
      return false;
    }
  
}

int recombineNumber(int first, int second)
{
  if(first == 0)
  {
    return second;
  }

  else if(first == 1)
  {
    if(second > 5)
    {
      Serial.println("Can not display that");
    }
    return second + 10;
  }

  else if(first >= 1)
  {
    Serial.println("Can not display that");

    return -1;
  }

  else
  {
    Serial.println("Can not display that");
    
    return -1;
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
  delay(50);
  /*********************************************************************************************************/
}

void watchdogTimerSetup()
{

  /*Reset the watchdog reset counter*/
  wdtResetCount = 0;
  /*********************************/

  /*disable interupts*/
  cli();
  /*******************/

  /*Clear all watchdog flags*/
  MCUSR = 0; 
  /**************************/

  /*Set watchdog in config mode*/
  WDTCSR |= 0b00011000;
  /*****************************/
  
  /*Set watchdog in interupt only and set prescaler to 1 second*/
  WDTCSR =  0b01000000 | 0b000110;
  /*************************************************************/

  /*Renable interupts*/
  sei();
  /*******************/
  
}

ISR(WDT_vect) // watchdog timer interrupt service routine
{
  /*Increment watchdog reset counter*/
  wdtResetCount++;
  /**********************************/


  /*If three seconds has not passed*/
  if(wdtResetCount != 2)
  {
    wdt_reset(); // start timer again (still in interrupt-only mode)
  }
  /*********************************/

 else
 {
   /*Reset watchdog flags*/
   MCUSR = 0;
   /**********************/           

   /*Enter config mode*/
   WDTCSR |= 0b00011000;
   /*******************/

   Serial.println("No input detected, resetting system ...");
   /*Set watchdog in reset mode only and set timer to 16 MS*/
   WDTCSR =  0b00001000 | 0b000000;
   /********************************************************/
 }
}

void resetProcedure()
{
  /*Enters method to clear serial input stream*/
  clearSerialInput();
  /********************************************/

  wdt_reset();

  /*Reset the counter back to 0*/
  wdtResetCount = 0;
  /*****************************/
}

