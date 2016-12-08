#include "stdint.h.h"
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
	//initIrSend();
	GameInit();

	while (1);

	return 1;
}
