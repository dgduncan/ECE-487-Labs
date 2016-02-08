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

int reading;
int buttonState = HIGH;
int lastDebounceTime;
int lastButtonReading = HIGH;
int userInteractions = 0;




void setup() 
{
  /*Initialize pin13 LED and pin12 as output*/
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, INPUT); 
  /******************************************/
  
  /*Set the baud rate, begin serial, and print intial prompt*/
  Serial.begin(9600);
  /**********************************************************/
}

void loop() 
{
  checkReading();
}

void checkReading()
{
  segmentDisplay.displayHex(userInteractions);
  /*Get the current value on pin11*/
  reading = digitalRead(11);
  /********************************/

  /*If the state of the button is changing, reset the debounceTimer*/
  if(reading != lastButtonReading)
  {
    lastDebounceTime = millis();
  }
  /****************************************************************/

  
  if(((millis() - lastDebounceTime) > 200))
  {
    if(reading != buttonState)
    {
      buttonState = reading;

      if(buttonState == LOW)
      {
        displayDataToUser();
      }
    }
    
    blinkLED();
  }

  lastButtonReading = reading;
  
  

  
  
}

void displayDataToUser()
{
  Serial.print("Decimal: ");
  Serial.print(++userInteractions);
  Serial.print(" HEX:");
  Serial.println(userInteractions, HEX);
  segmentDisplay.displayHex(userInteractions);

  
}

void blinkLED()
{
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

  else
  {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  }
}
