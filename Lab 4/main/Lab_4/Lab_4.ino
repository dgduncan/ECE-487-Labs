/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 4
 * 2/21/2016
 */

void setup() 
{
  Serial.begin(9600);
  Serial.println("Please input the character 'c' into the serial input, other inputs will be rejected");
  
  

}

void loop() 
{
  if(checkSerial(); == 'c')
  {
    beingAnalogReads();
  }
  

}

void beginAnalogReads()
{
  int analogData;
  int readTime;
  int startOfRead;
  
  for(int i = 0; i <= 30; i++)
  {
    startOfRead = millis();
    
    analogData = analogRead(4);

    readTime = millis() - startOfRead;

    displayResults();
  }
}

void displayResults(int readSequence, int analogData, int readTime)
{
  Serial.print("#");
  Serial.print(readSequence);
  Serial.print("  ");
  Serial.print("Digital Value = ");
  Serial.print((HEX) analogData);
  Serial.print("  ");
  Serial.print("Time = ");
  Serial.print(readTime);
  Serial.println(" usecs");
}

char checkSerial()
{
  /*Initialized character y */
  char firstCharacter;
  /*************************/

  /*Checks if there are more than 2 characters in the stream*/
  if(Serial.available() > 2)
  {
    /*Notifies user that they messed up*/
    Serial.println("Please only input 1 character");
    /**********************************/

    /*Enters method to clear serial input stream*/
    clearSerialInput();
    /*******************************************/

    /*Return meaningless character*/
    return 'a';
    /******************************/
  }
  /**********************************************************/

  else
  {
    /*Read first byte of the stream*/
    firstCharacter = Serial.read();
    /*******************************/

    /*Enters method to clear serial input stream*/
    clearSerialInput();
    /********************************************/

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
