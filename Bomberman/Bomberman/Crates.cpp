#include "Crates.h"

/* function used to generate crates into the game */
uint8_t* GenerateCrates(){
	uint8_t *c;
	/* make variables with a malloc of 127 */
	c = (uint8_t*)malloc(127);

	/* randomSeed generates a number with analogRead as seed,
	since analogRead differs in value, the output of randomSeed
	will differ to, but it will be equal for the same seed
	every time */
	randomSeed(analogRead(0));

	/* an 8-bit integer x is declared as 2, to be used in
	the following code */
	uint8_t x = 2;

	/* for-loop loops through all the 127 possible crates */
	for (uint8_t i = 0; i < 127; i++){
		/* the default location of crate is set to outside the playing field */
		c[i] = 0xFF;
	}

	/* for-loop loops through all the 127 possible crates */
	for (uint8_t i = 0; i < 127; i++){
		/* this randomly skips a crate location to make the playing field random */
		if (random(2) == 1){
			x++;
		}

		/* if the crate is not on the right location, it will skip the crate
		until the right location is found */
		while ((x & 0x0F) > 0x0C || ((x & 0x0F) % 2 == 1 && ((x & 0xF0) >> 4) % 2 == 1) || x == 0x10 || x == 0xBC){
			x++;
		}
		
		/* the generating of crates will stop if the last possible location
		of the crate has been reached */
		if (x >= 0xCB){
			break;
		}

		/* sets a bomb location */
		c[i] = x;
		x++;
	}
	return c;
}