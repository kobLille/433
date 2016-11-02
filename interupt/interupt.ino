/*
 Input Pullup Serial

 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
 digital input on pin 2 and prints the results to the serial monitor.

 The circuit:
 * Momentary switch attached from pin 2 to ground
 * Built-in LED on pin 13

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.

 created 14 March 2012
 by Scott Fitzgerald

 http://www.arduino.cc/en/Tutorial/InputPullupSerial

 This example code is in the public domain

 */

#define maxi 600
unsigned int val[maxi];
unsigned long  memo, tampon;
bool trame[100];
int i, j, k, l, ok;

void setup() {
  //start serial connection
  Serial.begin(230400);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, blink, RISING);

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
  // else
  //   ok = 1;
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
