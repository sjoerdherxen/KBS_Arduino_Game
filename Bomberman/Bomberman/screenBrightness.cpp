#include "screenBrightness.h"

uint16_t brightness = 0;

void setupPot() {
	/* setup pin A0 (PORTC0) as input for the potentiometer */
	DDRC &= ~(1 << PORTC0);
}

uint16_t analogReadPot(uint8_t pin) {

	/* make the two vars low and high for the output value */
	uint8_t low, high;

	/*  A0 is represented as pin 14, see pins_arduino.h */
	if (pin >= 14) pin -= 14;

	/* this sets the analog reference to DEFAULT and sets ADLAR to 0 */
	ADMUX = (DEFAULT << 6) | (pin & 0x07);

	/* sbi() is a macro to set the bit of the address to 1, setting the ADCSRA
	to 1 begins the AD conversion */
	sbi(ADCSRA, ADSC);

	/* wait for the conversion to finish. the bit_is_set() is a macro that checks
	if the second argument bit of the first argument is 1. if it finishes it becomes 0 */
	while (bit_is_set(ADCSRA, ADSC));

	/* the results of the conversion are stored in ADCL and ADCH */
	low = ADCL;
	high = ADCH;

	/* connect the results to make a 16-bit value to output */
	return (high << 8) | low;
}

uint8_t setBrightness() {
	/* analogRead() outputs the value of A0, this is put into the var brightness */
	brightness = analogReadPot(A0);

	/* shift brightness to the right two times to change the value to a value that
	the led screen accepts as a value */
	brightness = (brightness >> 2);

	/* return the created brightness */
	return brightness;
}