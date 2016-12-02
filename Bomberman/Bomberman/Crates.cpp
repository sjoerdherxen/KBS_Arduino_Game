#include "Crates.h"

// voor het genereren van kratten
uint8_t* GenerateCrates(){
	uint8_t *c;
	c = (uint8_t*)malloc(127); // maak variablen
	randomSeed(analogRead(0)); // random seed maken
	uint8_t x = 2;
	for (uint8_t i = 0; i < 127; i++){
		c[i] = 0xFF; // standaard locatie van krat op buiten veld zetten.
	}

	for (uint8_t i = 0; i < 127; i++){
		// zo af en toe een kratlocatie overslaan
		if (random(2) == 1){
			x++;
		}
		// als krat op niet juiste locatie is dan deze overslaan totdat er een goede locatie is.
		while ((x & 0x0F) > 0x0C || ((x & 0x0F) % 2 == 1 && ((x & 0xF0) >> 4) % 2 == 1) || x == 0x10 || x == 0xBC){
			x++;
		}
		// als de laatst mogelijke locatie van de kratten is bereikt dan stoppen
		if (x >= 0xCB){
			break;
		}
		// set bom locatie
		c[i] = x;
		x++;
	}
	return c;
}