#include <IRremote.h>
#include <Bounce.h>

IRsend irsend; // the IR transmit pin is 10, also requires a 1k resistor

const int buttonPin = 20; //The button is on pin 20 and ground
const int ledPin = 15; //The LED inside the button is pin 15
int brightness = 30; //a variable for the LED inside the button
int fadeamount = 1;

Bounce pushbutton = Bounce(buttonPin, 10);  // 10 ms debounce

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); //set as input with pullup resistor
  pinMode(ledPin, OUTPUT);
}


void loop() {
  pushbutton.update ( ); // Update the debouncer 
  int value = pushbutton.read(); // Get the update value
  
  if ( value == HIGH) {
    //pulse the LED inside the button 
     analogWrite(ledPin, brightness);
     brightness = brightness + fadeamount;
     if (brightness == 30 || brightness == 255) {
        fadeamount = -fadeamount;
        }
     delay(20);      
  }
  else {
     analogWrite(ledPin, 0);
     irsend.sendNEC(0xC40BF, 32); //send Benq power button signal
     delay(100);
     irsend.sendNEC(0xCF300FF, 32); //send Sanyo power button pressed
     delay(100);
     irsend.sendNEC(0xC73FF00, 32); //send Sanyo power button released
  }
}