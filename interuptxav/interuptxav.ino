/*

  created 14 March 2012
  by Scott Fitzgerald
  http://domotique.idleman.fr/radiograph.htm
  http://www.arduino.cc/en/Tutorial/InputPullupSerial
*/

#define maxi 100
unsigned int val[maxi];
unsigned long  memo, tampon;
bool trame[100], recuta[32];
int i, j, k, l, ok, x , w;
long  Adresse  = 0;

void blink()
{
  val[i] = (int)(micros() - memo);  // valeur temps dans tableau val ( i )
  memo = micros();
  if (i++ >= maxi) i = 0;         //i >=maxi 600 compteur ( i ) 0
}

void setup() {
  Serial.begin(230400);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, blink, RISING);
}

void loop() {
  //  bool trame[100];
  if (j != i) {
    if (val[j]) {          //valeur temps dans tableau val addrese ( j )
      noInterrupts();
      tampon = val[j];        //ecri temps dans tableau val addrese ( j )
      interrupts();
      //      if (tampon > 2500)     //conparession temps
      if (tampon < 420 || tampon > 2750) {
        ok = 1;
        //        Serial.println("");
        //                Serial.println(" ========    Trame ================================ ");
      }
      else {
        if (tampon > 1380) {    //conparession temps 750
          trame[k] = 1;       //ecri ( 1 ) tabeau trame
          Serial.print("1");
        }
        else {
          Serial.print("0");
          trame[k] = 0;
        }         //ecri ( 0 ) tabeau trame
        k++;
      }                   //incrémente k de un, sans modifier k
      val[j] = 0;
    }              //pointeur ( j ) debut val
    if (j++ >= maxi) j = 0;
    //j >=maxi 600 compteur ( j ) 0
    //    Serial.println("");
    //    Serial.println("=============FIN Trame====================================================== " );
  }
  if (ok) {
    l = 0, x = 0;                     // renialiser compteur ( l )
    while (l < k && k != 0) {    // k != 0 (k est différent de 0
      if (trame[l] == 1 && trame[l + 1] == 0) {
        recuta[x] = 1;
        //        Serial.print("1");
      }
      else {
        recuta[x] = 0;
        //        Serial.print("0");
      }
      l = l + 2;          //( l) +2
      x = x + 1;
    }
    //    Serial.println("");
    //    Serial.println("=============26====================================================== " );
    x = 0;
    while (x < 25) {
      //      Serial.print(recuta[x]);
      x = x + 1;
    }
    //    Serial.println("");
    //    Serial.println("==============26  BIN FIN=============================== " );
    x = 0 ;
    w = 25;
    while (w >= 0) {
      bitWrite (Adresse, w, 0);
      bitWrite (Adresse, w, recuta[x]);
      x = x + 1 ;
      w = w - 1 ;
    }
    //    Serial.println(Adresse, BIN);
    //    Serial.println("        ===== Raport Addresse ======= ===");
    //    Serial.print(recuta[27]);
    //    Serial.println("                 ===== Raport Groupe ======= ");
    //    Serial.print(recuta[28]);
    //    Serial.println("                 ===== Raport Action ======= ");
    //    Serial.print(recuta[28]);
    //    Serial.print(recuta[29]);
    //    Serial.print(recuta[30]);
    //    Serial.print(recuta[31]);
    //    Serial.println("              ===== Raport Intrerruteur ======= ");
    //    Serial.println(" =========================================== " );
    ok = 0;                     // renialiser compteur ( ok )
    k = 0;                      // renialiser compteur ( k )
    Serial.print("Adresse  ");
    //    Serial.println(Adresse, BIN);
    Serial.println(Adresse);
    //    Serial.println(" ==================fin===================== " );
  }
}

