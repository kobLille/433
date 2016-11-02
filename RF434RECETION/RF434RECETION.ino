/******************************************************************************
* RF434 decode for ARDUINO/Energia
*
* Description: This RF434MHz decoding was retturn by Bharadwaaj for decoding the codes encoded by EV1527. This
*              Code works fine with both MSP430 based Energia as well as Arduino.
*
* Author: Bharadwaaj RA
* Source
* Email: bhaaradwaaj@gmail.com
* Date: 04/01/2013
*
* Note: Any bug reports or issues feel free to contact the author.
*       Also note that the Data pin should be connected to Pin2.
******************************************************************************/
#define PREAMBLE_PERIOD 10000//10000
#define MIN_LOW_TIME 200             //#define MIN_LOW_TIME 200
#define NO_OF_BITS 72                //#define NO_OF_BITS 24
#define ADD_NO_OF_BITS 20            //#define ADD_NO_OF_BITS 20
#define KEY_NO_OF_BITS 4             //#define KEY_NO_OF_BITS 4
#define THER_LOW_PERIOD 700          //#define THER_LOW_PERIOD 700
void setup() {
  Serial.begin(9600);
  Serial.println("Demarrage");
}
short unsigned int i = 0;
short unsigned int a[72] = {0,};
short unsigned int temp = 0;
unsigned long add_val = 0;
unsigned long add_val1 = 0;
short unsigned int key = 0;
void loop() {

  add_val = 0;
  key = 0;
  add_val1 = 0;
  temp = pulseIn(3, LOW);
  Serial.println(temp);
  if (temp >= PREAMBLE_PERIOD)            //10000
  {
    while (i < NO_OF_BITS)                //#define NO_OF_BITS 24
    {
      temp = pulseIn(3, LOW);
      if (temp > MIN_LOW_TIME);           //#define MIN_LOW_TIME 200
      {
        a[i++] = temp;
      }
    }
    for (i =  0; i < 72; i++)     //#define NO_OF_BITS 24
    {
      Serial.print(a[i]);
      a[i] = 0;
    }


  }

  i = 0;

}
