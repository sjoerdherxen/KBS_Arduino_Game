#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"
#include "showLives.h"
#include <util/delay.h>

uint8_t crates[127];

int main(void) {
	setupExpander();												//Set the ports that are needed to output power to the leds

	while (1) {
		startLives();
		
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
	// feature
}