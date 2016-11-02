
const int buttonPin = 6;
unsigned long duration;
int i, j;
int tab[64];

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  duration = 0;
  duration = pulseIn(buttonPin, LOW);
  //Serial.println(duration);
  if (duration > 2500)
  {
    Serial.println(" debut");
    i = 0;
    while (i < 64)
    {
      duration = 0;
      duration = pulseIn(buttonPin, LOW);
      delay(1);
      if (duration > 2500)

      {
//        while (j < i)
//        {
//          if (tab[j] == 1)
//            Serial.print("1");
//          else
//            Serial.print("0");
//          j = j + 1;
//        }
//        j = 0;
//        Serial.println();
////        while (j < i)
//        {
//          if (tab[j] == 1 && tab[j + 1] == 0)
//            Serial.print("1");
//          else
//            Serial.print("0");
//          j = j + 2;
//        }
        Serial.print(" ");
        Serial.print(i);
        i = 0;
        j = 0;
        duration = 0;
        Serial.println();
      }
      else
      {
        // Serial.println("coucou1");
        if (duration > 500)
          tab[i] = 1;
        else
          tab[i] = 0;
        Serial.print(" ");
         Serial.print(duration);
         Serial.print("\t");
        duration = 0;
        i++;
      }
    }

    Serial.println("fin");
  }
}
