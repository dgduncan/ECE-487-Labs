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


/*Flag to tell when the LEDs should be blinking*/
boolean blinkFlag;
/***********************************************/

/*The interval I want the LEDs to blink for*/
long blinkInterval = 1000;
/*******************************************/

/*This is the initial state of the button*/
int buttonState;
/*****************************************/

/*This is the reading that happened in the previous loop through*/
int lastButtonReading = HIGH;
/****************************************************************/

/*This is the time in milliseconds that the last debounce happened*/
int lastDebounceTime;
/******************************************************************/

/*The current state of the LED*/
int ledState;
/******************************/

/*The time in milliseconds that the previous blink occured*/
unsigned long previousMillis = 0;
/**********************************************************/

/*This is the current reading of the button*/
int reading;
/*******************************************/

/*The number of times the counter hit max and "rollover" occures*/
int rollover = 0;
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

  /*Check the initial conditions of the circuit*/
  checkInitialConditions();
  /*********************************************/
}

void loop() 
{
  /*Check the reading on the button*/
  checkReading();
  /*********************************/

  /*Go through blink loop*/
  blinkLED();
  /***********************/
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

      if(buttonState == LOW)
      {
        blinkFlag = true;
      }
      else
      {
        blinkFlag = false;
      }

      /*Display current data to the user*/
      displayDataToUser();
      /**********************************/

    }
    /****************************************************************************/

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
  Serial.print(" HEX: ");
  Serial.print(userInteractions, HEX);
  Serial.print(" Rollover: ");//Because Dr. Ricks mentioned
  Serial.println(rollover);
  /*************************************************************/

  /*Display user button interactions with the seven-segment*/
  segmentDisplay.displayHex(userInteractions); 
  /*********************************************************/

  checkIfRollover();
}
/******************************************************************************/

/*Method to handle the blinking of the LEDs*/
void blinkLED()
{
  /*Enter if the blink flag is set to true*/
  if(blinkFlag)
  {
    /*Current time in Milliseconds*/
    unsigned long currentMillis = millis();
    /******************************/
    
    /*Enter if more than 1 seconds has passed*/
    if (currentMillis - previousMillis >= blinkInterval)
    {
      /*Save the current state*/
      previousMillis = currentMillis;
      /************************/
  
      /*Switch the states of the LEDs*/
      if (ledState == LOW)
      {
        ledState = HIGH;
      } 
      else 
      {
        ledState = LOW;
      }
      /********************************/
  
      /*Change pin states*/
      digitalWrite(12, ledState);
      digitalWrite(13, !ledState);
      /*******************/
    }
  }
  /***************************************/

  
  /*Make sure the LEDs are off*/
  else
  {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  /****************************/
  
}

/*Method to check if rollover occurs*/
void checkIfRollover()
{
  /*Add to rollover and reset user interactions*/
  if(userInteractions == 15)
  {
    rollover++;
    userInteractions = -1;
  }
  /*********************************************/
}
/************************************/

/*Method to check the initial conditions of the circuit*/
void checkInitialConditions()
{
  /*Set current state of button*/
  buttonState = digitalRead(11);
  /*****************************/

  /*Choose correct state based on button state*/
  if(buttonState == LOW)
  {
    blinkFlag = true;
  }
  else
  {
    blinkFlag = false;
  }
  /*********************************************/
}
/**********************************************/

