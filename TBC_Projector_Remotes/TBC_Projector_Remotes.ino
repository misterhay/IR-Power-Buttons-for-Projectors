#include <IRremote.h>

IRsend irsend;

const int buttonSanyoPin = 20; //The Sanyo button is on pin 20 and ground
const int buttonBenqPin = 21; //The Benq button is on pin 21 and ground

void setup() {
  pinMode(buttonSanyoPin, INPUT_PULLUP); //set as input with pullup resistor
  pinMode(buttonBenqPin, INPUT_PULLUP); //set as input with pullup resistor
}

void loop() {
if (digitalRead(buttonBenqPin)) {
 if (digitalRead(buttonBenqPin)) {
   }
 else {
       irsend.sendNEC(0xC40BF, 20); //send Benq power button signal
       delay(100);
      }
   }
else {
    irsend.sendNEC(0xCF300FF, 20); //send Sanyo power button pressed
    delay(100);
    irsend.sendNEC(0xC73FF00, 20); //send Sanyo power button released
    delay(100);
     }
}
