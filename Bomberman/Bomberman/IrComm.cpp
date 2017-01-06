#include "IrComm.h"

volatile uint8_t datasend = 0;
unsigned long prevMicros = 0;

volatile uint8_t data = 0;
uint8_t *received;
uint8_t Pdata = 0;
uint8_t PrevDataItemSend = 1;
uint8_t PrevDataItemRec = 0;

volatile uint8_t sendData = 0;
volatile uint8_t sendDataByte = 0;
volatile uint8_t sendDataBit = 7;
volatile uint8_t sendDataStage = 0;
volatile uint8_t *dataToSend;
volatile unsigned long millisSendDone = 0;
uint8_t timer2count = 0;

void setupIR(){

	PORTD |= (1 << PIND3);
	DDRD |= (1 << PIND3);

	DDRD &= ~(1 << PIND2);
	PORTD |= (1 << PIND2);

	//while (1);
	EICRA = 1;	// pinchange on falling/rising edge pd2 / pin2
	EIMSK = 1;  // Set interupt enable on pin 2

	//set up Timer 2
	//TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
	cli();
	TCCR2B = (1 << CS21);// | (1 << CS20); // prescaler 32
	TCCR2A = (1 << WGM21);
	// time = 500 us
	OCR2A = 249;
	TIMSK2 |= (1 << OCIE2A);
	sei();


	received = (uint8_t *)malloc(5);
	dataToSend = (uint8_t *)malloc(5);
}


// send 3 bytes of information. and receive checksum byte
void sendTrippleStart(uint8_t b1, uint8_t b2, uint8_t b3){
	// set data to send bytes
	dataToSend[0] = (PrevDataItemSend++) & 0x07;
	dataToSend[1] = b1;
	dataToSend[2] = b2;
	dataToSend[3] = b3;
	dataToSend[4] = (PrevDataItemSend + b1 + b2 + b3) & 0x0F;

	// activate data sender protocol
	sendData = 1;
	sendDataBit = 8;
	sendDataByte = 0;
	sendDataStage = 0;
}

uint8_t sendTrippleDone(uint8_t b1, uint8_t b2, uint8_t b3){
	while (sendData || millis() - millisSendDone < 6); // wait for datasend to be done and 6 ms has passed, should be enough for other to send response
	return (received[0] == (PrevDataItemSend + b1 + b2 + b3) & 0x0F);
}
//received[0] = 0;
//Pdata = 0;
//if (PrevDataItemSend >= 7)
//	PrevDataItemSend = 0;
//else
//	PrevDataItemSend++;

//IrSendByte(PrevDataItemSend, 2);
//IrSendByte(b1, 7);
//IrSendByte(b2, 7);
//IrSendByte(b3, 7);
//IrSendByte((PrevDataItemSend + b1 + b2 + b3), 4);
//while (1){

//	Pdata = 0;
//	_delay_ms(10);
//	if (received[0] == (uint8_t)((PrevDataItemSend + b1 + b2 + b3) & 0x1F)){
//		break;
//	}
//	IrSendByte(PrevDataItemSend, 2);
//	IrSendByte(b1, 7);
//	IrSendByte(b2, 7);
//	IrSendByte(b3, 7);

//	IrSendByte((PrevDataItemSend + b1 + b2 + b3), 4);
//}
//_delay_ms(10);


void IrSendByte(uint8_t byte){
	// set byte data 
	dataToSend[4] = byte;
	// activate data sender protocol
	sendData = 1;
	sendDataBit = 8;
	sendDataByte = 4;
	sendDataStage = 0;

	// todo convert to timer1
	// start sequence

	/*
	PORTD &= ~(1 << PIND3);
	_delay_us(450);

	// loop bits
	for (int8_t i = byteSize; i >= 0; i--){
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
	*/
}

uint8_t* dataRecieve(){
	if (datasend){
		if ((uint8_t)((uint8_t)(received[0] + received[1] + received[2] + received[3]) & 0x1F) == received[4]){
			IrSendByte(received[4] & (0x0F));

			if (received[0] != PrevDataItemRec){
				PrevDataItemRec = received[0];
				return received;
			}
			PrevDataItemRec = received[0];
			//IrSendByte(received[0] + received[1] + received[2] + received[3], 2);
		}
		else {
			IrSendByte(0x1F);
		}
		datasend = 0;
	}
	return 0;
}

uint8_t dataAvailable(){
	return datasend;
}

// pinchange op pin2,van hoog naar laag en andersom.
ISR(INT0_vect){
	unsigned long time = micros() - prevMicros;
	prevMicros = micros();
	uint8_t input = (PIND & (1 << PIND2));
	if (input){ // pin 2 is on
		if (time < 750){ // 0
			data = data << 1;
		}
		else if (time < 1250){ // 1
			data = data << 1;
			data |= 1;
		}
	}
	else{ // pin 2 is off
		if (time < 750){
			// tussen 1 bit
		}
		else if (time < 1250){
			// end of byte
			received[Pdata++] = data;
			data = 0;
		}
		else{
			// start of data;
			Pdata = 0;
			data = 0;
		}
	}
}


ISR(TIMER2_COMPA_vect){
	if (timer2count < 3){
		timer2count++;
		return;
	}
	timer2count = 0;

	if (!sendData){
		return;
	}
	if (sendData == 2){
		PORTD |= (1 << PIND3);
		return;
	}
	if (sendData == 3){
		millisSendDone = millis();
		return;
	}

	switch (sendDataStage)
	{
	case 0:
		if (sendDataBit > 0){
			PORTD |= (1 << PIND3);
			if (sendDataBit == 8){
				while (!sendDataByte & (1 << (sendDataBit - 1)) && sendDataBit > 2){
					sendDataBit--;
				}
			}
		}
		else{
			sendDataByte++;
			if (sendDataByte > 4){
				sendData = 2;
				return;
			}
			sendDataBit = 8;
			sendDataStage = 0;
			return;
		}
		break;
	case 1:
		if (!dataToSend[sendDataByte] & (1 << (sendDataBit - 1))){
			PORTD &= ~(1 << PIND3);
			sendDataBit--;
			sendDataStage = 0;
			return;
		}
		break;
	case 2:
		if (dataToSend[sendDataByte] & (1 << (sendDataBit - 1))){
			PORTD &= ~(1 << PIND3);
			sendDataBit--;
			sendDataStage = 0;
			return;
		}
		break;
	}

	sendDataStage++;
}