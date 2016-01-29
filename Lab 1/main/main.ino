/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 486
 * Lab 1
 * 1/29/2016
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  Serial.println("Type 'g' into the serial monitor to blink the LEDs and 's' to stop the blinking");

}

void loop() {
  /*Variable Initialization and first reading*/
  char userInput = Serial.read(); 
  /*******************************************/

  /*Check if user has input 'g' into serial monitor'*/
  if(userInput == 'g')
  {
    /*Notify the user that the LEDs are now blinking*/
    Serial.println("LEDs are now blinking");
    /***********************************************/
    
    /*Blinking loop until user enters 's' to stop.*/
    ledBlinking(userInput);
    /*********************************************/
  }
    

}

void ledBlinking(char userInput)
{
  while(userInput != 's')
    {
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      delay(2000);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      delay(1000);
      userInput = Serial.read();
    }

    /*Shut off LEDs*/
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    /***************/
    
    /*Notify User the LEDs are turned off*/
    Serial.println("LEDs are now off");
    /************************************/
}
