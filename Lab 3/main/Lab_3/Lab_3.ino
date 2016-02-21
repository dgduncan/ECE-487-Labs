#include <SegmentDisplay.h>
#include <avr/wdt.h>

/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 3
 * 2/11/2016
 */

/*Declare and Initalize the SegmentDisplay class with the appropriate pins*/
SegmentDisplay segmentDisplay(3, 2, 9, 8, 7, 6, 5, 4);

int wdtResetCount;

void setup() 
{
  /*Open Serial connection and display user prompt*/
  Serial.begin(9600);
  Serial.println("Please type in number to display on 7-Segment");

  /*Display decimal point to show that reset has occured*/
  segmentDisplay.displayDecimalPoint();

  /*Set up the watchdog timer*/
  watchdogTimerSetup();

}

void loop() 
{
  /*Variable Initialization and first reading*/
  checkSerial();
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

    segmentDisplay.displayHex(-1, false);

    resetProcedure();

    /*Return flag that tells if integer was displayed*/
    return false;
  }

  /*If there are two characters in the stream*/
  else if (Serial.available() > 2)
  {
    /*Read first and second byte of the stream*/
    int firstInt = Serial.read() - '0';
    int secondInt = Serial.read() - '0';

    /*If the two numbers returned are both numbers*/
    if(checkIfNumbers(firstInt, secondInt))
    {
      /*Enter reset protocol*/
      resetProcedure();

      /*Get the value of the two combined numbers*/
      int recombineInt = recombineNumber(firstInt, secondInt);

      /*Display the new number on the seven segment*/
      segmentDisplay.displayHex(recombineInt, false);

      /*If everything is ok*/
      if(recombineInt != -1)
      {
        Serial.print("Your input: ");
        Serial.println(recombineNumber(firstInt, secondInt));
      }

      return true;
    }

    else
    {
      segmentDisplay.displayHex(-1, false);
      /*Enter the reset procedure*/
      resetProcedure();
      
      return false;
    }
  }

  /*If there is only one character in the stream*/
  else if(Serial.available() > 1)
  {
    /*Get the integer from the serial*/
    int firstInt = Serial.read() - '0';

    /*If the number is within bounds*/
    if(firstInt >= 0 && firstInt <= 9)
    {
      /*Enter reset procedure*/
      resetProcedure();

      /*Display the integer on the seven segment*/
      segmentDisplay.displayHex(firstInt, false);

      /*Display input on serial monitor*/
      Serial.print("Your input: ");
      Serial.println(firstInt);
      
      return true; 
    }
    else
    {
      /*Notify user that they are wrong*/
      Serial.println("Can not display that");

      /*Display an error code*/
      segmentDisplay.displayHex(-1, false);

      /*Enter reset procedure*/
      resetProcedure();
      
      return false;
    }
  }
}  

/*Check if the two integers are indeed numbers*/
boolean checkIfNumbers(int first, int second)
{
  /*If both of the numbers are good return true, else return false*/
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

/*Recombine the two integers received*/
int recombineNumber(int first, int second)
{
  /*If there is a zero to start*/
  if(first == 0)
  {
    return second;
  }

  /*If there are two numbers*/
  else if(first == 1)
  {
    if(second > 5)
    {
      Serial.println("Can not display that");
    }
    return second + 10;
  }

  /*If the data is indicating out of range*/
  else if(first >= 1)
  {
    Serial.println("Can not display that");

    return -1;
  }
  
  /*If nothing looks right*/
  else
  {
    Serial.println("Can not display that");
    
    return -1;
  }
}

/*Procedure to clear the serial input*/
void clearSerialInput()
{
  /*While loop to clear all data in the serial input stream*/
  while(Serial.available())
  {
    Serial.read();
  }

  /*Apparently there is some delay in clearing the data, so delay prevents a double run through of the code*/
  delay(50);
}

/*Procedure to set up the watch dog timer*/
void watchdogTimerSetup()
{

  /*Reset the watchdog reset counter*/
  wdtResetCount = 0;

  /*disable interupts*/
  cli();

  /*Clear all watchdog flags*/
  MCUSR = 0; 

  /*Set watchdog in config mode*/
  WDTCSR |= 0b00011000;
  
  /*Set watchdog in interupt only and set prescaler to 1 second*/
  WDTCSR =  0b01000000 | 0b000110;

  /*Renable interupts*/
  sei();
  
}

ISR(WDT_vect) // watchdog timer interrupt service routine
{
  /*Increment watchdog reset counter*/
  wdtResetCount++;

  /*If three seconds has not passed*/
  if(wdtResetCount != 2)
  {
    wdt_reset(); // start timer again (still in interrupt-only mode)
  }

 else
 {
   /*Reset watchdog flags*/
   MCUSR = 0;         

   /*Enter config mode*/
   WDTCSR |= 0b00011000;

   Serial.println("No input detected, resetting system ...");
   /*Set watchdog in reset mode only and set timer to 16 MS*/
   WDTCSR =  0b00001000 | 0b000000;
 }
}


void resetProcedure()
{
  /*Enters method to clear serial input stream*/
  clearSerialInput();

  Serial.println("Resetting Watchdog Timer ...");
  wdt_reset();

  /*Reset the counter back to 0*/
  wdtResetCount = 0;

}

