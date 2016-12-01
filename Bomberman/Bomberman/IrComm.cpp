#include "IrComm.h"

 uint8_t datasend = 0;

void initIrSend(){
	cli();

	DDRD |= (1 << PIND2);
	EICRA = 2;	// pinchange on falling edge pd2 / pin2
	EIMSK = 1;  // Set interupt enable on pin 2

	DDRB |= 1 << PORTB3;

	//set up Timer 2
	TCCR0A = _BV(COM0A0) | _BV(WGM01);  // CTC, toggle OC2A on Compare Match
	TCCR0B = _BV(CS00);   // No prescaler
	OCR0A = 209;

	sei();
}

void IrSendByte(uint8_t byte){
	uint8_t paraty = 0;
	DDRB = 0;
	_delay_us(100);
	for (uint8_t i = 0; i < 8; i++){
		DDRB |= 1 << PORTB3;
		_delay_us(100);
		DDRB &= ~(1 << PORTB3);
		_delay_us(100);
		if (byte & (1 << i)){
			paraty ^= 1;
			_delay_us(100);
		}
	}
	DDRB |= 1 << PORTB3;
	_delay_us(100);
	DDRB &= ~(1 << PORTB3);
	_delay_us(100);
	if (paraty){
		_delay_us(100);
	}
	DDRB |= 1 << PORTB3;
	_delay_us(100);
}

ISR(INT0_vect) {

}
