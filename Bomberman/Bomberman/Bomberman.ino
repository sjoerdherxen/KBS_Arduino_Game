#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>
#include <Wire.h>

#include "BasicDisplay.h"
#include "MainMenu.h"
#include "Crates.h"
#include "Nunchuck.h"
#include "Game.h"

int main(void){
	init();
	Serial.begin(19200);
	Nunchuck_setpowerpins(); // use analog pins 2&3 as fake gnd & pwr
	Nunchuck_init(); // send the initilization handshake
	Serial.print("Finished setup\n");

	GameInit();

	return 1;
}