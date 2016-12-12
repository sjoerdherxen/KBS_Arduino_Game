#include "stdint.h"
#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

int main(void){
	init();
	//initIrSend();
	Serial.begin(9600);
	GameInit();

	while (1);

	return 1;
}
