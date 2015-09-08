#include <IRremote.h>
/* you may need to comment out two lines in energia\hardware\msp430\libraries\IRremote\IRremote.cpp:
//  pinMode(TIMER_PWM_PIN, OUTPUT);
//  digitalWrite(TIMER_PWM_PIN, LOW); // When not sending PWM, we want it low
*/

IRsend irsend; // the IR transmit pin is 11, also requires a 50-150 ohm resistor
const int powerButton = 5; //The power button on this pin and ground
const int inputButton = 6; //The input button on this pin and ground
const int led1 = 14; //The heartbeat LED
const int led2 = 2; //The transmission status LED

int brightness = 30; //variables for the heartbeat LED
int fadeamount = 5;

void setup() {
  pinMode(powerButton,INPUT_PULLUP);
  pinMode(inputButton,INPUT_PULLUP);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void sendIR(int buttonPressed) {
 analogWrite(led1, 0); // turn off the led so we know something is happening
 digitalWrite(led2, HIGH); // turn on the red status LED so we know something is happening
 if (buttonPressed == 1) {irsend.sendNEC(0xCF318E7, 32);} // send the power button signal
 if (buttonPressed == 2) {irsend.sendNEC(0xCF310EF, 32);} // send the input button signal
 digitalWrite(P2_3, LOW); // turn off the IR LED when not transmitting
 delay(1000); // wait for a second
}

void heartbeat() {
 digitalWrite(led2, LOW); // turn the red status LED off
 analogWrite(led1, brightness);
 brightness = brightness + fadeamount;
 if (brightness == 30 || brightness == 255) {fadeamount = -fadeamount;}
 delay(5);
}

void loop() {
 if (digitalRead(powerButton) == LOW) {sendIR(1);}
 else if (digitalRead(inputButton) == LOW) {sendIR(2);}
 else {heartbeat();}
}
