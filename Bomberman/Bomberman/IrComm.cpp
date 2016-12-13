#include "IrComm.h"

volatile uint8_t datasend = 0;
volatile unsigned long prevMicros = 0;
volatile uint8_t data = 0;
uint8_t *received;
volatile uint8_t Pdata = 0;

void initIrSend(){

	PORTD |= (1 << PIND3);
	DDRD |= (1 << PIND3);

	DDRD &= ~(1 << PIND2);
	PORTD |= (1 << PIND2);

	//while (1);
	EICRA = 3;	// pinchange on falling edge pd2 / pin2
	EIMSK = 1;  // Set interupt enable on pin 2

	cli();
	//set up Timer 1
	TCCR1B = _BV(WGM12) | (1 << CS10);
	TCCR1A = _BV(COM1A0);
	OCR1A = 209;

	sei();
	received = (uint8_t *)malloc(4);
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
	/*Serial.print(b1);
	Serial.print("-");
	Serial.print(b2);
	Serial.print("-");
	Serial.print(b3);
	Serial.print("-");
	Serial.println((uint8_t)(b1 + b2 + b3));*/

	IrSendByte(b1);
	IrSendByte(b2);
	IrSendByte(b3);
	IrSendByte(b1 + b2 + b3);

	while (1){
		Pdata = 0;
		_delay_ms(20);
		if (received[0] == (uint8_t)(b1 + b2 + b3)){
			break;
		}

		IrSendByte(b1);
		IrSendByte(b2);
		IrSendByte(b3);

		IrSendByte(b1 + b2 + b3);
	}
	_delay_ms(30);
}

void IrSendByte(uint8_t byte){
	// start sequence
	PORTD |= (1 << PIND3);
	_delay_us(450);

	//	Serial.println(byte);

	// loop bits
	for (uint8_t i = 0; i < 8; i++){
		if (byte & (1 << i)){
			_delay_us(450);
		}
		// set high
		PORTD &= ~(1 << PORTD3);
		_delay_us(450);
		// set low
		PORTD |= (1 << PORTD3);
		_delay_us(450);

	}
	// set high
	PORTD &= ~(1 << PORTD3);
	_delay_us(1750);

	// lange delay voor einde data
	PORTD |= (1 << PORTD3);
	_delay_us(450);
	PORTD &= ~(1 << PORTD3);

	_delay_us(3000);
}

uint8_t* dataRecieve(){
	if (datasend){
		Serial.print(received[0]);
		Serial.print("-");
		Serial.print(received[1]);
		Serial.print("-");
		Serial.print(received[2]);
		Serial.print("-");
		Serial.println(received[3]);
	
		if ((uint8_t)(received[0] + received[1] + received[2]) == received[3]){
			IrSendByte(received[0] + received[1] + received[2]);

			return received;
		}
		else {
			IrSendByte(0);
		}
		datasend = 0;
	}
	return 0;
}

uint8_t dataAvailable(){
	return datasend;
}

// pinchange op pin2,van hoog naar laag.
ISR(INT0_vect){
	unsigned long time = micros() - prevMicros;
	prevMicros = micros();
	//Serial.println(time);
	if (time > 20000){
	}
	if (time > 2750){
		// start
	}
	else if (time > 1500){
		// end
		received[Pdata] = data;
		data = 0;
		Pdata++;
		if (Pdata == 4){
			datasend = 1;
			Pdata = 0;
		}
	}
	else { // bit waarde
		if (time > 1120){
			// 1
			data = data >> 1;
			data |= 0x80;
		}
		else if (time > 750){
			data = data >> 1;
			// 0
		}
	}
}