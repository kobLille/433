const int buttonPin = 6;
const int ledPin =  13;
unsigned long duration;
int i, j;
int tab[64];
int ledState = LOW;    

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
}

void loop() {
    Serial.print(digitalRead(buttonPin));
    Serial.println();
  duration = 0;
  duration = pulseIn(buttonPin, LOW);
  if (duration > 2500)
  {
     if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    Serial.println(duration);
   
  }
}
