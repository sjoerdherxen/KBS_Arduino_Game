#include <Wire.h>
#include <Arduino.h>
#include <MI0283QT9.h>

#include "Textures.h"
#include "BasicDisplay.h"
#include "MainMenu.h"
#include "Crates.h"
#include "Nunchuck.h"
#include "Game.h"

int main(void){
	init();

	while (1) {
		startLives();
		GameInit();
		//vanaf hier testgedeelte om de leds te testen
		_delay_ms(1000);
		loseLife();
		_delay_ms(1000);
		loseLife();
		_delay_ms(1000);
		loseLife();
		_delay_ms(1000);
		loseLife();
		_delay_ms(1000);
		loseLife();										//Loses last life
		_delay_ms(3000);
		
	}
	return 0;
}
*/