#include "IrComm.h"

volatile uint8_t datasend = 0;
volatile unsigned long prevMicros = 0;
volatile uint8_t data = 0;
volatile uint8_t received[3];
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

void SendUpdateData(uint8_t playerlocation, uint16_t bomb){
	sendTripple(playerlocation, (bomb & 0xFF00) >> 8, bomb & 0x00FF);
}

void SendInitData(uint8_t seed){
	sendTripple(seed, 0, 0);
}


// send 3 bytes of information. and receive checksum byte
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3){
	received[0] = 0;
	Pdata = 0;
	IrSendByte(b1);
	IrSendByte(b2);
	IrSendByte(b3);

	while (1){
		Pdata = 0;
		_delay_ms(4);
		if (received[0] == (uint8_t)(b1 + b2 + b3)){
			break;
		}
		IrSendByte(b1);
		IrSendByte(b2);
		IrSendByte(b3);
	}
}

void IrSendByte(uint8_t byte){
	// start sequence
	PORTD &= ~(1 << PIND3);
	_delay_us(90);

	//	Serial.println(byte);

	// loop bits
	for (uint8_t i = 0; i < 8; i++){
		if (byte & (1 << i)){
			_delay_us(90);
		}
		// set high
		PORTD |= (1 << PORTD3);
		_delay_us(90);
		// set low
		PORTD &= ~(1 << PORTD3);
		_delay_us(90);

	}
	// set high
	PORTD |= (1 << PORTD3);
	_delay_us(350);

	// lange delay voor einde data
	PORTD &= ~(1 << PORTD3);
	_delay_us(90);
	PORTD |= 1 << PORTD3;

	_delay_us(600);
}

uint8_t dataRecieve(){
	if (datasend){
		IrSendByte(received[0] + received[1] + received[2]);
		datasend = 0;
		return received[0];
	}
	return 0;
}


// pinchange op pin2,van hoog naar laag.
ISR(INT0_vect){
	unsigned long time = micros() - prevMicros;
	prevMicros = micros();
	if (time > 550){
		// start
	}
	else if (time > 300){
		// end
		received[Pdata] = data;
		data = 0;
		Pdata++;
		if (Pdata == 3){
			datasend = 1;
			Pdata = 0;
		}
	}
	else { // bit waarde
		if (time > 225){
			// 1
			data = data >> 1;
			data |= 0x80;
		}
		else if (time > 150){
			data = data >> 1;
			// 0
		}
	}
}