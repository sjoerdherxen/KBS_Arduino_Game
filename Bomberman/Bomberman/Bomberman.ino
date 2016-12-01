#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

#include "IrComm.h"
#include "Textures.h"
#include "BasicDisplay.h"
#include "MainMenu.h"
#include "Crates.h"
#include "Nunchuck.h"
#include "Game.h"

int main(void){
	// init van arduino en init van het spel aanroepen.
	init();
	initIrSend();
	//GameInit();

	while (1);

	return 1;
}
