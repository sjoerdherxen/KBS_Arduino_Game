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
	//sendTripple(0xAA, 0xAA, 0xAA);
	sendTripple(seed, seed, seed);
}


// send 3 bytes of information. and receive checksum byte
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3){
	received[0] = 0;
	Pdata = 0;
	IrSendByte(b1);
	//IrSendByte(b2);
	//IrSendByte(b3);

	Serial.println("Sending");
	uint8_t i = 0;
	/*
	while (1){
		Pdata = 0;
		_delay_ms(10);
		if (received[0] == (uint8_t)(b1 + b2 + b3) || i == 0){
			Serial.println("received");
			break;
		}
		//IrSendByte(b1);
		//IrSendByte(b2);
		//IrSendByte(b3);
		i++;
	}*/
}

void IrSendByte(uint8_t byte){
	// start sequence
	PORTD &= ~(1 << PIND3);
	_delay_us(90);
	PORTD |= (1 << PIND3);
	_delay_us(90);
	PORTD &= ~(1 << PIND3);
	_delay_us(90);

	// loop bits
	for (uint8_t i = 0; i < 8; i++){
		// set high
		if (byte & (1 << i)){
			_delay_ms(90);
		}
		PORTD |= (1 << PORTD3);
		_delay_us(90);
		// set low
		PORTD &= ~(1 << PORTD3);
		_delay_us(90);
	}
	// set high
	PORTD |= (1 << PORTD3);
	_delay_us(90);

	// lange delay voor einde data
	PORTD &= ~(1 << PORTD3);
	_delay_us(450);
	PORTD |= 1 << PORTD3;

	_delay_us(1500);
}

void dataRecieve(){
	if (datasend){
		IrSendByte(received[0] + received[1] + received[2]);
		Serial.print(received[0]);
		Serial.print("-");
		Serial.print(received[1]);
		Serial.print("-");
		Serial.print(received[2]);
		Serial.println("--");
		datasend = 0;
	}
	if (data) {
		_delay_ms(1000);
		Serial.println(data);
		data = 0;
	}
}


// pinchange op pin2,van hoog naar laag.
ISR(INT0_vect){
	unsigned long time = micros() - prevMicros;
	prevMicros = micros();
	//Serial.println(time);
	if (time > 900){
		//Serial.print("-");
		//data = 0;
		// start
	}
	else if (time > 315){
		// end
		//Serial.println("end");
		received[Pdata] = data;
		//data = 0;
		Pdata++;
		if (Pdata == 3){
			datasend = 1;
			Pdata = 0;
		}
		//datasend = 1;
	}
	else { // bit waarde
		Serial.println(time);
		if (time > 225){
			// 1
			//Serial.println("bit1");
			data = data >> 1;
			//data |= 0x80;
		}
		else if (time > 150){
			//Serial.println("bit0");
			data = data >> 1;
			data |= 0x80;
			// 0
		}
		else {
			//Serial.print("?");
		}
	}
}