
#define ledPin 8
#define maxi 600

typedef struct requete requetes;
struct requete
{
  bool emetteur[26] ;
  bool groupe ;
  bool etat ;
  bool interupteur[4];
};

unsigned int val[maxi];
unsigned long  memo, tampon;
bool trame[100];
int i, j, k, l, ok;
requetes envoie[0];

void miseTampon()
{
  
}

void setup() {

  pinMode(ledPin, OUTPUT);
  //start serial connection
  Serial.begin(230400);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, blink, RISING);

  // initialiser le timer1
  noInterrupts(); // désactiver toutes les interruptions
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 31250; // 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // Activer le mode de comparaison
  interrupts(); // activer toutes les interruptions

}

void loop() {
  if (j != i)
  {
    if (val[j])
    {
      noInterrupts();
      tampon = val[j];
      interrupts();
      if (tampon > 2500)
      {
        ok = 1;
        Serial.println();
      }
      else
      {
        if (tampon > 750)
        {
          trame[k] = 1;
          Serial.print("1");
        }
        else
        {
          Serial.print("0");
          trame[k] = 0;
        }
        k++;
      }
      val[j] = 0;

    }
    if (j++ >= maxi) j = 0;
  }

  if (ok)
  {
    l = 0;
    while (l < k && k != 0)
    {
      if (trame[l] == 1 && trame[l + 1] == 0)
        Serial.print("1");
      else
        Serial.print("0");
      l = l + 2;
    }
    Serial.println();
    ok = 0;
    k = 0;
  }

  
}


void blink()
{
  val[i] = (int)(micros() - memo);
  memo = micros();
  if (i++ >= maxi) i = 0;
}


ISR(TIMER1_COMPA_vect) // fonction périodique
{
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1); // Basculer la LED allumée/éteinte

}

