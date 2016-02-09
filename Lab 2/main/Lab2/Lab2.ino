#include <SegmentDisplay.h>

/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 2
 * 2/03/2016
 */
 
/*Declare and Initalize the SegmentDisplay class with the appropriate pins*/
SegmentDisplay segmentDisplay(2, 3, 4, 5, 6, 7, 8, 9);
/*************************************************************************/

/*This is the current reading of the button*/
int reading;
/*******************************************/

/*This is the initial state of the button*/
int buttonState = HIGH;
/*****************************************/

/*This is the time in milliseconds that the last debounce happened*/
int lastDebounceTime;
/******************************************************************/

/*This is the reading that happened in the previous loop through*/
int lastButtonReading = HIGH;
/****************************************************************/

/*This is the number of times the button has changed states*/
int userInteractions = 0;
/***********************************************************/

void setup() 
{
  /*Initialize pin13 and pin12 as output, pin11 as input*/
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT); 
  /******************************************************/
  
  /*Set the baud rate, begin serial, and print intial prompt*/
  Serial.begin(9600);
  /**********************************************************/
}

void loop() 
{
  /*Check the reading on the button*/
  checkReading();
  /*********************************/
}

void checkReading()
{
  /*Display the inital value on the seven-segment*/
  segmentDisplay.displayHex(userInteractions);
  /***********************************************/
  
  /*Get the current value on pin11 i.e the state of the switch*/
  reading = digitalRead(11);
  /************************************************************/

  /*If the state of the button is changing, reset the debounceTimer*/
  if(reading != lastButtonReading)
  {
    lastDebounceTime = millis();
  }
  /****************************************************************/

  /*Go into this loop 200 miliseconds after debounce is triggered*/
  if(((millis() - lastDebounceTime) > 200))
  {
    /*If the current reading on pin11 is not the same as the state of the button*/
    if(reading != buttonState)
    {
      /*The current state of the button is now equal to the current reading*/
      buttonState = reading;
      /*********************************************************************/

      /*Display current data to the user*/
      displayDataToUser();
      /**********************************/

    }
    /****************************************************************************/

    /*Enter the LED loop*/
    blinkLED();
    /********************/
  }
  /***************************************************************/

  /*This will prevent debounce timer from resetting every time*/
  lastButtonReading = reading;
  /************************************************************/
  
  

  
  
}

/*Method to display data to the user and to increment user button interactions*/
void displayDataToUser()
{
  /*Print the decimal and hex value of user button interactions*/
  Serial.print("Decimal: ");
  Serial.print(++userInteractions);
  Serial.print(" HEX:");
  Serial.println(userInteractions, HEX);
  /*************************************************************/

  /*Display user button interactions with the seven-segment*/
  segmentDisplay.displayHex(userInteractions); 
  /*********************************************************/
}
/******************************************************************************/

/*Method that will either blink the LEDs or will shut them off*/
void blinkLED()
{
  /*If the current state of the button is LOW, begin to blink the LEDs*/
  if(buttonState == LOW)
  {
    /*Turn onboard LED on and off-board led off for 2 seconds*/
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    delay(1000);
    /*********************************************************/
  
    /*Do the opposite of above for 1 second*/
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    delay(1000);
    /***************************************/
  }
  /********************************************************************/

  /*If it is not, make sure the LEDs are off*/
  else
  {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  }
  /******************************************/
}
/***************************************************************/
