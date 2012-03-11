#include <IRremote.h>

IRsend irsend;

const int buttonPin = 20; //The "power" button is on pin 20 and ground

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); //set as input with pullup resistor
}

void loop() {
if (digitalRead(buttonPin)) {
 {
   }
 else {
    irsend.sendNEC(0xC40BF, 20); //send Benq power button signal
    delay(100);
    irsend.sendNEC(0xCF300FF, 20); //send Sanyo power button pressed
    delay(100);
    irsend.sendNEC(0xC73FF00, 20); //send Sanyo power button released
    delay(100);
     }
}