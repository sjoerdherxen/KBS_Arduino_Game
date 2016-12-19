#include "IrComm.h"

volatile uint8_t datasend = 0;
volatile unsigned long prevMicros = 0;
volatile uint8_t data = 0;
uint8_t *received;
volatile uint8_t Pdata = 0;
volatile uint8_t PrevDataItemSend = 1;
volatile uint8_t PrevDataItemRec = 0;


void setupIR(){

	PORTD |= (1 << PIND3);
	DDRD |= (1 << PIND3);

	DDRD &= ~(1 << PIND2);
	PORTD |= (1 << PIND2);

	//while (1);
	EICRA = 2;	// pinchange on falling edge pd2 / pin2
	EIMSK = 1;  // Set interupt enable on pin 2

	received = (uint8_t *)malloc(5);
}


// send 3 bytes of information. and receive checksum byte
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3){
	received[0] = 0;
	Pdata = 0;
	PrevDataItemSend++;
	IrSendByte(PrevDataItemSend);
	IrSendByte(b1);
	IrSendByte(b2);
	IrSendByte(b3);
	IrSendByte(PrevDataItemSend + b1 + b2 + b3);

	while (1){
		Pdata = 0;
		_delay_ms(20);
		if (received[0] == (uint8_t)(PrevDataItemSend + b1 + b2 + b3)){
			break;
		}
		IrSendByte(PrevDataItemSend);
		IrSendByte(b1);
		IrSendByte(b2);
		IrSendByte(b3);

		IrSendByte(PrevDataItemSend + b1 + b2 + b3);
	}
	_delay_ms(30);
}

void IrSendByte(uint8_t byte){
	// start sequence
	PORTD &= ~(1 << PIND3);
	_delay_us(450);

	// loop bits
	for (uint8_t i = 0; i < 8; i++){
		if (byte & (1 << i)){
			_delay_us(450);
		}
		// set high
		PORTD |= (1 << PORTD3);
		_delay_us(450);
		// set low
		PORTD &= ~(1 << PORTD3);
		_delay_us(450);

	}
	// set high
	PORTD |= (1 << PORTD3);
	_delay_us(1750);

	// lange delay voor einde data
	PORTD &= ~(1 << PORTD3);
	_delay_us(450);
	PORTD |= (1 << PORTD3);

	_delay_us(3000);
}

uint8_t* dataRecieve(){
	if (datasend){
		if ((uint8_t)(received[0] + received[1] + received[2] + received[3]) == received[4]){
			IrSendByte(received[0] + received[1] + received[2] + received[3]);

			if (received[0] != PrevDataItemRec){
				PrevDataItemRec = received[0];
				return received;
			}
			PrevDataItemRec = received[0];
			IrSendByte(received[0] + received[1] + received[2] + received[3]);
		}
		else {
			IrSendByte(255);
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
	if (time > 20000){
		Pdata = 0;

	}
	if (time > 2750){
		// start
	}
	else if (time > 1500){
		// end
		received[Pdata] = data;
		data = 0;
		Pdata++;
		if (Pdata == 5){
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