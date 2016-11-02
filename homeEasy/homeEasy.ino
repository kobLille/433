int ledPin = 13;
int rxPin = 6;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(rxPin, INPUT);
   Serial.begin(9600);   

}
boolean readBit()
{
  unsigned long t;
  do {
    t = pulseIn(rxPin, HIGH);
  } while (t < 300 || t > 1500);
 
  return t > 750;
}

void latch()
{
  boolean b = readBit();
  while (!b) {
    b = readBit();
  }
}


void loop() {
  // put your main code here, to run repeatedly:

 int i = 0;
  unsigned long d = 0;
  unsigned int data = 0;
  unsigned long t;
 
  while (i < 25) {
    // wait for first pulse to latch
    Serial.print(digitalRead(rxPin));
    Serial.print(" ");
    //t = pulseIn(rxPin, HIGH, 1500);
    t = pulseIn(rxPin, LOW);
    Serial.print(i);
   Serial.print(" ");
     Serial.println( t);
    // pulses are expected to be either 375us or 1125us, but there's
    // some tolerance here.
    if (t < 200 || t > 2500) {
      // pulse timing off or timeout - reset
      i = 0;
      data = 0;
      Serial.println("coucou");
      continue;
    }
 Serial.println("titi");
//    if (i % 2 == 0) {
//        if (t > 400) {
//        // should be zero pulses
//        i = 0; data = 0;
//        Serial.println("coucou1");
//        continue;
//      }
//    }
//    else {
      data = (data>>1) + (t > 400 ? 0x800 : 0);
  //  }
 
    ++i;
  }
 
  int group = data & 15;
  int unit = (data >> 4) & 15;
  int cmd = (data >> 8) & 15;
 
  Serial.print(" group: ");
  Serial.print(group+65, OCT);
  Serial.print(" unit: ");
  Serial.print(unit+1);
  Serial.print(" cmd: ");
  Serial.print((cmd == 14 ? "ON" : (cmd == 6 ? "OFF" : "UNK")));
  Serial.println();  

}
