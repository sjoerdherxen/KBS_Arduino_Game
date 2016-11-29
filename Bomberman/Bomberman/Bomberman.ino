#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"
#include "showLives.h"
#include <util/delay.h>

uint8_t crates[127];
int lives = 0;

int main(void) {
	setupPorts();												//Set the ports that are needed to output power to the leds

	while (1) {
		startLives(&lives);											//5 Leds are on

		//vanaf hier testgedeelte om de leds te testen
		_delay_ms(3000);
		loseLife(&lives);
		_delay_ms(3000);
		loseLife(&lives);
		_delay_ms(3000);
		loseLife(&lives);
		_delay_ms(3000);
		loseLife(&lives);
		_delay_ms(3000);
		loseLife(&lives);										//Loses last life
		_delay_ms(3000);
	}
	return 0;
	// feature
}