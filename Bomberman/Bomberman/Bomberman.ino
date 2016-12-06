#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

//#include "IrComm.h"
#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

#define MasterGame
//#define SlaveGame

//uint8_t crates[127];

int main(void){
	init();
	initIrSend();
	//GameInit();
	Serial.begin(9600);
	while (1){
		//IrSendByte(170);
		//_delay_ms(1000);
		dataRecieve();
		if (Serial.available()){
			Serial.println(Serial.readString());
			SendInitData(0x11);
		}
	}

	return 1;
}
