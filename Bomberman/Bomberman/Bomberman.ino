#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"
#include "MainMenu.h"
#include "Crates.h"
#include "Nunchuck.h"
#include "Game.h"

int main(void){
	init();

	GameInit();

	return 1;
}