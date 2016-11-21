#include "Crates.h"

uint8_t* GenerateCrates(){
	uint8_t *c;
	c = (uint8_t*)malloc(127);
	randomSeed(analogRead(0));
	uint8_t x = 2;
	for (uint8_t i = 0; i < 127; i++){
		if (random(2) == 1){
			x++;
		}
		while ((x & 0x0F) > 0x0C || ((x & 0x0F) % 2 == 1 && ((x & 0xF0) >> 4) % 2 == 1) || x == 0x10 || x == 0xBC){
			x++;
		}

		if (x >= 0xCB){
			break;
		}
		c[i] = x;
		x++;
	}

	return c;
}