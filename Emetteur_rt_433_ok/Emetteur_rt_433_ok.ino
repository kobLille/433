/*
 * HE300 Automatic Protocol Transmitter 'Simulator'
 *
 * This demo code emits a homeeasy automatic protocol ON message 
 * then 3 seconds later, an off message
 *
 * You dont need to learn the Arduino into the socket, because it can 
 * pretend to be a transmitter you already have.
 *
 * Use the Automatic protocol reciever code above to find out
 * your transmitter address 8-)
 *
 * *Only* tested with one HE300 transmitter (HE Address 272946) with its
 * slider switch set to 1 which appears to be 0 in fact.
 * Seems to work with a switch socket (HE302S) and can turn it on and off 
 * without the ardunio being learned into the socket.
 *
 * Martyn Henderson 02/10/2009  http://martgadget.blogspot.com
 *
 * Cheers to Barnaby and Peter, because without the code above
 * that shows the receiver output this wouldnt have been possible!
 *
 * If you make something cool using HomeEasy and Arduino, please 
 * post back here with a link to your code so we can all enjoy.
 */
/*
  * HE300 automatique de l'émetteur Protocole 'Simulator'
  *
  * Ce code de démonstration émet un protocole automatique HomeEasy ON Message
  * Puis 3 secondes plus tard, un message hors
  *
  * Vous ne devrez apprendre l'Arduino dans la prise, car il peut
  * Faire semblant d'être un émetteur que vous avez déjà.
  *
  * Utilisez le code protocole de récepteur automatique ci-dessus pour en savoir
  * Votre adresse de l'émetteur 8-)
  *
  * * * Seulement testé avec un émetteur de HE300 (HE Adresse 272 946) avec son
  * Interrupteur à glissière mis à 1 qui semble être 0 en fait.
  * Semble fonctionner avec une prise de commutation (HE302S) et peut tourner sur et en dehors
  * Sans ardunio être appris dans la prise.
  *
  * Martyn Henderson 02/10/2009 http://martgadget.blogspot.com
  *http://playground.arduino.cc/Code/HomeEasy
  *Bravo à Barnaby et Peter, parce que sans le code ci-dessus
  * Montre que la sortie du récepteur cette wouldnt aurait été possible!
  *
  * Si vous faites quelque chose de cool utilisant HomeEasy et Arduino, s'il vous plaît
  * Poster revenir ici avec un lien vers votre code afin que nous puissions tous en profiter.
  */

bool bit2[20]={};              // 26 bit global to store the HE device address.       26 bits globale pour stocker l'adresse du dispositif SE.
int txPin = 2;                 // 433mhz transmitter on pin2                          Transmetteur de 433mhz sur pin2

void setup()
{
  pinMode(txPin, OUTPUT);      // transmitter pin.                                     broches de l'émetteur.
  Serial.begin(9600);         // console port                                          le port console

  Serial.println("go");

  itob(21,16);
  // convert our device code..                              convertir notre code de l'appareil.

  transmit(true);            // send ON                                                envoyer sur
  delay(10);                 // wait (socket ignores us it appears unless we do this)  wait (socket nous ignore, il semble que si nous faisons cela)
  transmit(true);            // send ON again                                          Envoyer sur nouveau

  delay(3000);               // wait 3 sec   delay(3000);                                          attendre 3 secondes

  transmit(false);           // and off again.                                        et repart.
  delay(10);
  transmit(false);


  Serial.println("stop");    // done.                                                  terminé.

}
void loop()
{
 
}


void transmit(int blnOn)
{
  int i;

  // Do the latch sequence.. 
  digitalWrite(txPin, HIGH);
  delayMicroseconds(175);     // bit of radio shouting before we start. peu de cris de radio avant de commencer 275.
  digitalWrite(txPin, LOW);                  //peu de cris de radio avant de commencer. Peu de cris de la radio avant de Commencer.
  delayMicroseconds(9900);     // low for 9900 for latch 1              bas pour 9900 pour verrouillage 1
  digitalWrite(txPin, HIGH);   // high again                            haute nouveau
  delayMicroseconds(175);      // wait a moment 275                     attendre un moment 275
  digitalWrite(txPin, LOW);    
  delayMicroseconds(500);    // low again for 2675 - latch 2.         faible encore pour 2 675 - 2 loquet.
  // End on a high                                                      Terminez sur une haute
  digitalWrite(txPin, HIGH);

  // Send HE Device Address..                                           Envoyer HE Adresse du périphérique ..
  // e.g. 1000010101000110010  272946 in binary.                        par exemple 1000010101000110010 272946 en binaire.
  for(i=0; i<20;i++)
  {
    sendPair(bit2[i]);
    Serial.print("   bits  -> ");
    Serial.print(i);
    Serial.print("  ");
  Serial.println (bit2[i]);
  }

  // Send 26th bit - group 1/0                                          Envoyer 26 bits - groupe 1/0
  sendPair(false);
 Serial.println("Envoyer 26 bits - groupe 1/0");
  Serial.println(false);
  // Send 27th bit - on/off 1/0                                         Envoyer 27 bits - on / off 1/0
  sendPair(blnOn);
Serial.println("Envoyer 27 bits - on / off 1/0");
  Serial.println(blnOn);
  // last 4 bits - recipient   -- button 1 on the HE300 set to          4 derniers bits - bénéficiaire - le bouton 1 sur le HE300 mis à
  // slider position I in this example:                                 curseur position I dans cet exemple:

  sendPair(false);
  sendPair(false);
  sendPair(false);
  sendPair(false);

  digitalWrite(txPin, HIGH);   // high again (shut up)                 encore élevé (fermer)
  delayMicroseconds(900);      // wait a moment                        attendez un moment
  digitalWrite(txPin, LOW);    // low again for 2675 - latch 2.        faible encore pour 2 675 - 2 loquet.

}


void sendBit(boolean b) {
  if (b) {
    digitalWrite(txPin, HIGH);
    delayMicroseconds(800);   //275 orinally, but tweaked.            275 orinally, mais tordu.
    digitalWrite(txPin, LOW);
    delayMicroseconds(700);  //1225 orinally, but tweaked.           1,225 orinally, mais tordu.
  }
  else {
    digitalWrite(txPin, HIGH);
    delayMicroseconds(100);   //275 orinally, but tweaked.           275 orinally, mais tordu.
    digitalWrite(txPin, LOW);
    delayMicroseconds(100);   //275 orinally, but tweaked.           275 orinally, mais tordu.
  }
}

void sendPair(boolean b) {
  // Send the Manchester Encoded data 01 or 10, never 11 or 00       Envoyez le Manchester données codées 01 ou 10, 11 ou 00 ne
  if(b)
  {
    sendBit(true);
    sendBit(false);
  }
  else
  {
  sendBit(false);
  sendBit(true);
  }
}


void itob(unsigned long integer, int length)
{  //needs bit2[length]                                                  besoins bit2 [longueur]
  //Convert long device code into binary (stores in global bit2 array.)  Autre code long de périphérique dans binaires (magasins en réseau bit2 mondiale.)
 for (int i=0; i<length; i++){
   if ((integer / power2(length-1-i))==1){
     integer-=power2(length-1-i);
     bit2[i]=1;
   }
   else bit2[i]=0;
 }
}

unsigned long power2(int power){    //gives 2 to the (power)              donne 2 à la (puissance)
 unsigned long integer=1;          
 for (int i=0; i<power; i++){      
   integer*=2;
 }
 return integer;
}
