/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
 int toto;

void setup() {
  pinMode(4, OUTPUT);
    Serial.begin(9600);
  Serial.println("début");
  mySwitch.enableReceive(1);  // Receiver on interrupt 0 => that is pin #2
  
}

void loop() {
 // Serial.print("pin: " );
 // Serial.println( digitalRead(3));
//if (toto )
//  toto--;
//  else
//  toto=1000;
//  
//  
//if (!toto)
//  digitalWrite(4, digitalRead(4) ^ 1);
//
//Serial.print(toto);
//Serial.print(" ");
//Serial.println(digitalRead(3));
 
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
   
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }
}
