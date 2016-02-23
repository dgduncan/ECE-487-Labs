/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 4
 * 2/21/2016
 */

 unsigned long timesToAverage[30];

void setup() 
{
  /*Open Serial to begin communication and prompt user for input*/
  Serial.begin(9600);
  Serial.println("Please input the character 'c' into the serial input, other inputs will be rejected");
  Serial.println("");
}

void loop() 
{
  /*Only act if a 'c' is read on the serial*/
  checkSerial();
}

void beginAnalogReads()
{
  /*The analog data that will be read*/
  int analogData;

  /*The total time in milliseconds that it took to read from analog pin*/
  unsigned long readTime;

  /*The time in millis when the read was first begun*/
  unsigned long startOfRead;

  /*Prompt user that readings are about to take place*/
  Serial.println("");
  Serial.println("A series of 30 measurements are about to begin");
  Serial.println("");
  
  for(int i = 1; i <= 30; i++)
  {
    /*Mark the beginning of the analog read*/
    startOfRead = micros();

    /*The data returned from the analog pin*/
    analogData = analogRead(0);

    /*The time it took for the arduino to read from the pin*/
    readTime = micros() - startOfRead;

    /*A running count of the times that it took to read*/
    timesToAverage[i] = readTime;

    /*Display the results to the user from each read*/
    displayResults(i, analogData, readTime);

    /*Delay the read time so that the pin does not get overloaded*/
    delay(600-readTime);
  }
}

/*Displaying data in accordance to lab parameters*/
void displayResults(int readSequence, int analogData, int readTime)
{
  /*Required output as per lab parameters*/
  Serial.print("#");
  Serial.print(readSequence);
  Serial.print("  ");
  Serial.print("Digital Value = ");
  Serial.print(analogData, HEX);
  Serial.print("  ");
  Serial.print("Time = ");
  Serial.print(readTime);
  Serial.println(" usecs");

  /*If this is the final read, display the avergage and prompt user again for input*/
  if(readSequence == 30)
  {
    /*The average value from all 30 reads*/
    unsigned long average;

    /*Count all of the times from the array*/
    for(int i = 0; i < 30; i++)
    {
      average += timesToAverage[i];
    }

    /*Output average time and prompt user for another input*/
    Serial.println("");
    Serial.println("Average conversion time: ");
    Serial.print((average / 30));
    Serial.println(" usecs");
    Serial.println("");
    Serial.println("Please input the character 'c' into the serial input, other inputs will be rejected");
    Serial.println("");
  }
}

void checkSerial()
{
  /*Delay to allow all characters to be read into serial monitor*/
  delay(100);
  
  /*Initialized character y */
  char firstCharacter;

  /*Checks if there are more than 2 characters in the stream*/
  if(Serial.available() > 2)
  {
    /*Notifies user that they messed up*/
    Serial.println("Error : Multiple characters detected, please use correct input");

    /*Enters method to clear serial input stream*/
    clearSerialInput();

  }

  /*Check if there is a single character availabe in the serial*/
  else if(Serial.available() > 1)
  {
    /*Read first byte of the stream*/
    firstCharacter = Serial.read();

    /*Enters method to clear serial input stream*/
    clearSerialInput();

    /*detect a non 'c' character*/
    if (firstCharacter != 'c')
    {
      /*Prompt user that error has occured*/
      Serial.println("Error : non 'c' character detected, please use correct input");
    }
    else
    {
      /*Begin readings if 'c' has been read on serial*/
      beginAnalogReads();
    }
  }
}

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
