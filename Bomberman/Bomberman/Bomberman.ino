#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"


uint8_t crates[127];
uint8_t xx;

int main(void){
	init();
	randomSeed(analogRead(0));
	uint8_t x = 2;
	for (uint8_t i = 0; i < 127; i++){
		if (random(5) == 1){
			x++;
		}
		while ((x & 0x0F) > 0x0C || ((x & 0x0F) % 2 == 1 && ((x & 0xF0) >> 4) % 2 == 1) || x == 0x10 || x == 0xBC){
			x++;
		}
		
		if (x >= 0xCB){
			break;
		}
		crates[i] = x;
		x++;
	}

	xx = 0;
	DisplayOn();
	DisplayGame(crates, 0x00, 0xCC);

	while (1){
		_delay_ms(50);
		uint8_t oldCrates[127];
		for (int i = 0; i < 127; i++){
			oldCrates[i] = crates[i];
		}
		if (xx >= 127){
			xx = 0;
		}
		crates[xx] = 0xFF;
		UpdateGame(oldCrates, crates, 0x00, 0xBC, 0xCC, 0x01);
		xx++;
	}

	return 0;
	// feature
}