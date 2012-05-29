#include <IRremote.h>
#include <Bounce.h>

const int buttonPin = 20; //The button is on pin 20 and ground
const int RECV_PIN = 6; //The IR receiver is on pin 6
const int ledPin = 15; //The LED inside the button is pin 15
IRsend irsend; //the IR transmit pin is 10, also requires a 1k resistor
//PWM pin 12 is disabled by the IR transmit pin

//for IR receiving
IRrecv irrecv(RECV_PIN);
decode_results results;

int brightness = 30; //a variable for the pulsing LED inside the button
int fadeamount = 1; //a variable for the pulsing LED

Bounce pushbutton = Bounce(buttonPin, 10);  // 10 ms debounce

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); //set as input with pullup resistor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); //start the IR receiver
  irrecv.blink13(true); //blink the onboard LED when IR signal received
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
  
  
  // check out http://www.arcfn.com/2009/09/arduino-universal-remote-record-and.html
  //get values from from the IR receiver and output to serial
//  if (irrecv.decode(&results)) {
//    if (results.decode_type == NEC) {
//      Serial.print("NEC: ");
//      irsend.sendNEC(IRcode, numBits);
//    } else if (results.decode_type == SONY) {
//      Serial.print("SONY: ");
//    } else if (results.decode_type == RC5) {
//      Serial.print("RC5: ");
//    } else if (results.decode_type == RC6) {
//      Serial.print("RC6: ");
//    } else if (results.decode_type == UNKNOWN) {
//      Serial.print("UNKNOWN: ");
//    }
//    Serial.println(results.value, HEX);
//    irrecv.resume(); // Receive the next value
//  }
  
}
