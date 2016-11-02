volatile int state = LOW;
unsigned long val, memo;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, blink, CHANGE);
}
void loop() {
  if (val >4800& < 10600)
  {
    Chacon ();
  }
  else if (val >4800 )
  {
    HomeConfort ();
  }
}
void blink() {
  val = micros() - memo;
  memo = micros() ;
}
void HomeConfort() {
  Serial.print("===HomeConfort==========   ");
  Serial.println(val);
  if (val > 300) {
    Serial.print("                HomeConforte 111&       :");
    Serial.println(val);
  }
  else  {
    Serial.print("                         HomeConfort   0000   :");
    Serial.println(val);
  }
}
void Chacon () {
  Serial.print("=========== Chacon====================== ");
  Serial.println(val);
}

