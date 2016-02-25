/*
 * Derek Duncan
 * CWID: 11387683
 * ECE 487
 * Lab 3
 * 2/11/2016
 */

unsigned long timesToAverage[30];

unsigned long averageTime = 0;

void setup() 
{
  /*Open Serial connection and display user prompt*/
  Serial.begin(9600);
  Serial.println("Input an 'a' to read the analog pin using analogRead().");
  Serial.println("Input a 'b' to read the analog pin using direct port manipulation.");

  /*Set up the analog to digital converter*/
  adcSetUp();
}

void loop() 
{
  char userInput = checkSerial();

  switch (userInput)
  {
    case 'z':
      break;

    case 'a':
      useAnalogRead();
      break;

    case 'b':
      usePortManipulation();
      break;

    default:
      break;
      
  }

  

}


void usePortManipulation()
{

  unsigned long startOfRead;
  
  unsigned long readTime;

  /*Prompt user that readings are about to take place*/
  Serial.println("");
  Serial.println("A series of 30 measurements are about to begin");
  Serial.println("");
  

  for(int i = 0; i <= 30; i++)
  {
    startOfRead = micros();
    
    /*Start the analog read*/
    ADCSRA |= 0b01000000;

    while((ADCSRA & 0b00010000) != 16);

    Serial.println(micros() - startOfRead);

    //pollForChange(startOfRead, readTime);

    delay(500);
  }

  
  
}

void pollForChange(unsigned long startOfRead, unsigned long readTime)
{
  while((ADCSRA & 0b00010000) != 16);

  Serial.println(micros() - startOfRead);

  /*if((ADCSRA & 0b00010000) == 16)
  {
    readTime = micros() - startOfRead;

    averageTime += readTime;

    Serial.println(readTime);
    
    return;
  }

  else
  {
    pollForChange(startOfRead, readTime);
  }*/
  
}

void adcSetUp()
{
  /*Set the ADC mux to use AVcc as the reference*/
  ADMUX |= 0b01000000;
  
  /*Turn on the ADC on the Atmega2560 to prepare for reads*/
  ADCSRA |= 0b10000000;
}

void useAnalogRead()
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
    Serial.println("Input an 'a' to read the analog pin using analogRead().");
    Serial.println("Input a 'b' to read the analog pin using direct port manipulation.");
    Serial.println("");
  }
}

char checkSerial()
{
  /*Delay to allow all characters to be read into serial monitor*/
  delay(50);
  
  /*Initialized character y */
  char firstCharacter;

  /*Checks if there are more than 2 characters in the stream*/
  if(Serial.available() > 2)
  {
    /*Notifies user that they messed up*/
    Serial.println("Error : Multiple characters detected, please use correct input");

    /*Enters method to clear serial input stream*/
    clearSerialInput();

    return 'z';

  }

  /*Check if there is a single character availabe in the serial*/
  else if(Serial.available() > 1)
  {
    /*Read first byte of the stream*/
    firstCharacter = Serial.read();

    /*Enters method to clear serial input stream*/
    clearSerialInput();

    return firstCharacter;
  }

  return 'z';
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

