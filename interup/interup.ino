/*
  Input Pullup Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
  digital input on pin 2 and prints the results to the serial monitor.

  The circuit:
   Momentary switch attached from pin 2 to ground
   Built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to
  read HIGH when the switch is open, and LOW when it is closed.

  created 14 March 2012
  by Scott Fitzgerald
  http://domotique.idleman.fr/radiograph.htm
  http://www.arduino.cc/en/Tutorial/InputPullupSerial

  This example code is in the public domain

*/

#define maxi 100
unsigned int val[maxi];
unsigned long  memo, tampon;
bool trame[100], recuta[32];
int i, j, k, l, ok, x , q;
boolean f = false;//int f = 0;

void setup() {
  Serial.begin(230400);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, blink, RISING);

}

void loop() {
  if (j != i)
  {
    if (val[j])           //valeur temps dans tableau val addrese ( j )
    {
      noInterrupts();
      tampon = val[j];        //ecri temps dans tableau val addrese ( j )
      interrupts();
      //      if (tampon > 2500)     //conparession temps
      if (tampon < 420 || tampon > 2750)
      {
        ok = 1;
        Serial.println("");
        Serial.println(" ========    Trame ======= ");
      }
      else {
        if (tampon > 1380) {    //conparession temps 750
          trame[k] = 1;       //ecri ( 1 ) tabeau trame
          Serial.print("1");
        }
        else {
          Serial.print("0");
          trame[k] = 0;         //ecri ( 0 ) tabeau trame
        }
        k++;                   //incrémente k de un, sans modifier k
      }
      val[j] = 0;              //pointeur ( j ) debut val
    }
    if (j++ >= maxi) j = 0;     //j >=maxi 600 compteur ( j ) 0
  }
  //  Serial.println("        fin");
  if (ok)
  {
    l = 0, x = 0;                     // renialiser compteur ( l )

    while (l < k && k != 0)     // k != 0 (k est différent de 0
    {
      if (trame[l] == 1 && trame[l + 1] == 0)
      {
        recuta[x] = 1;
        Serial.print("1");
      }
      else
      {
        recuta[x] = 0;
        Serial.print("0");
      }
      l = l + 2;          //( l) +2
      x = x + 1;
    }
    Serial.println("");
    Serial.println("==============1=============================== " );
    x = 0;
    while (x < 26)
    {
      Serial.print(recuta[x]);
      x = x + 1;
    }
    Serial.println("");
    Serial.println("==============2=============================== " );
    x = 0, f = 0;
    while (x < 15)
    {
//      Serial.print(recuta[x]);
      f = recuta[x];
      f << 1;
//      Serial.print("-");
      Serial.print((f), BIN);
//      Serial.print(" ");
      x = x + 1 ;
    }
    Serial.println("     ===== Raport Addresse ======= ");
    Serial.print((f[]), BIN);
    Serial.println("              ============== f =============");
    Serial.print(recuta[27]);
    Serial.println("                 ===== Raport Groupe ======= ");
    Serial.print(recuta[28]);
    Serial.println("                 ===== Raport Action ======= ");
    Serial.print(recuta[28]);
    Serial.print(recuta[29]);
    Serial.print(recuta[30]);
    Serial.print(recuta[31]);
    //    Serial.print(recuta[32]);
    //    int w=(recuta[56],recuta[58],recuta[60],recuta[62]);
    Serial.println("              ===== Raport Intrerruteur ======= ");
    //        Serial.println(w);
    Serial.println("=========================================== " );
    ok = 0;                     // renialiser compteur ( ok )
    k = 0;                      // renialiser compteur ( k )

  }
}


void blink()
{
  val[i] = (int)(micros() - memo);  // valeur temps dans tableau val ( i )
  memo = micros();
  if (i++ >= maxi) i = 0;         //i >=maxi 600 compteur ( i ) 0

