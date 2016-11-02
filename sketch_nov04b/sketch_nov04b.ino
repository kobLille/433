/*
  433 MHz RF REMOTE REPLAY sketch
     Written by ScottC 24 Jul 2014
     Arduino IDE version 1.0.5
     Website: http://arduinobasics.blogspot.com
     Receiver: XY-MK-5V      Transmitter: FS1000A/XY-FST
     Description: Use Arduino to receive and transmit RF Remote signal
 ------------------------------------------------------------- */

#define rfReceivePin A0     //RF Receiver data pin = Analog pin 0

const int dataSize = 500;  //Arduino memory is limited (max=1700)
byte storedData[dataSize];  //Create an array to store the data
const unsigned int threshold = 100;  //signal threshold value
int maxSignalLength = 255;   //Set the maximum length of the signal
int dataCounter = 0;    //Variable to measure the length of the signal
const unsigned int upperThreshold = 100;  //upper threshold value
const unsigned int lowerThreshold = 80;  //lower threshold value
unsigned long startTime = 0; //Variable to record the start time
unsigned long endTime = 0;  //Variable to record the end time
unsigned long signalDuration = 0; //Variable to record signal reading time

void setup() {
  Serial.begin(9600);    //Initialise Serial communication - only required if you plan to print to the Serial monitor

}

void loop() {
  initVariables();
  listenForSignal();
  affichage();


  delay(20);
}


/* ------------------------------------------------------------------------------
    Initialise the array used to store the signal
   ------------------------------------------------------------------------------*/
void initVariables() {
  for (int i = 0; i < dataSize; i++) {
    storedData[i] = 0;
  }

}


/* ------------------------------------------------------------------------------
    Listen for the signal from the RF remote. Blink the RED LED at the beginning to help visualise the process
    And also turn RED LED on when receiving the RF signal
   ------------------------------------------------------------------------------ */
void listenForSignal() {
  // delay(1000);
 while(analogRead(rfReceivePin)<1){
      //Wait here until a LOW signal is received
      startTime=micros();  //Update start time with every cycle.  
  }
 
  
  //Read and store the rest of the signal into the storedData array
  for(int i=0; i<dataSize; i=i+2){
    
    //Identify the length of the LOW signal---------------LOW
    dataCounter=0; //reset the counter
    while(analogRead(rfReceivePin)>upperThreshold && dataCounter<maxSignalLength){
      dataCounter++;
    }
    storedData[i]=dataCounter;
    
    //Identify the length of the HIGH signal---------------HIGH
    dataCounter=0;//reset the counter
    while(analogRead(rfReceivePin)<lowerThreshold && dataCounter<maxSignalLength){
      dataCounter++;
    }
    storedData[i+1]=dataCounter;
  }
  }

  void affichage() {
    for (int i = 0; i < dataSize; i = i + 2) {
      Serial.print(storedData[i]);
      Serial.print(",");
      Serial.print(storedData[i+1]);
      Serial.print(";");
    }
    Serial.println("fin");
  }
  /*   ---------------------------------- */

