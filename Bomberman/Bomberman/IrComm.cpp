#include "IrComm.h"

volatile uint8_t datasend = 0;
volatile unsigned long prevMicros = 0;
volatile uint8_t data = 0;
volatile uint8_t Pdata = 0;

void initIrSend(){
	PORTD |= (1 << PIND3);
	DDRD |= (1 << PIND3);

	DDRD &= ~(1 << PIND2);
	PORTD |= (1 << PIND2);
	EICRA = 2;	// pinchange on falling edge pd2 / pin2
	EIMSK = 1;  // Set interupt enable on pin 2

	//set up Timer 2
	/*
	TCCR2A = _BV(COM2A0) | _BV(WGM21);  // CTC, toggle OC2A on Compare Match
	TCCR2B = _BV(CS20);   // No prescaler
	OCR2A = 209;
	*/
}

void IrSendByte(uint8_t byte){
	uint8_t paraty = 0;

	// start sequence
	PORTD &= ~(1 << PIND3);
	_delay_us(30);

	// loop bits
	for (uint8_t i = 0; i < 8; i++){
		// set high
		PORTD |= 1 << PORTD3;
		_delay_us(30);
		// set low
		PORTD &= ~(1 << PORTD3);
		_delay_us(30);
		// als bit is 1 dan langer laag blijven en invert parity
		if (byte & (1 << i)){
			paraty ^= 1;
			_delay_us(30);
		}
	}
	// set high
	PORTD |= 1 << PORTD3;
	_delay_us(30);

	// parity tonen
	PORTD &= ~(1 << PORTD3);
	_delay_us(30);
	if (paraty){
		_delay_us(30);
	}
	PORTD |= 1 << PORTD3;


	// lange delay voor einde data
	PORTD &= ~(1 << PORTD3);
	_delay_us(150);
	PORTD |= 1 << PORTD3;

	_delay_us(30);
}

void dataRecieve(){
	if (datasend){
		Serial.println(data);
		datasend = 0;
	}
}

// pinchange op pin2,van hoog naar laag.
ISR(INT0_vect){
	unsigned long time = micros() - prevMicros;
	prevMicros = micros();
	if (time > 300){
		//start
		//Pdata = 0;
		datasend = 1;
	}
	else if (time > 105){
		// end
		data = 0;
		Pdata = 0;
		datasend = 1;
	}
	else { // bit waarde
		if (Pdata & 7 == 7){
			return;
			if ((Pdata & 0x80 && time < 75) || (!(Pdata & 0x80) && time > 75)){// 0x80 is eerste bit
				data = 0xFF; // fout bij data parity klopt niet
			}
		}
		else if (time > 75){
			// 1
			Pdata ^= 0x80; // 0x80 is eerste bit
			data = data >> 1;
			data |= 0x80;
		}
		else if (time > 50){
			data = data >> 1;
			// 0
		}
		Pdata++;
	}
}