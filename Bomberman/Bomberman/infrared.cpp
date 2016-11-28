#include "infrared.h"

void setupIR() {
	DDRB &= ~(1 << PORTB3);
	Serial.begin(9600);
	Serial.println("setup done");
}

void readIR() {
	while (1) {
		int input = digitalRead(11);
		Serial.println(input);
	}
}