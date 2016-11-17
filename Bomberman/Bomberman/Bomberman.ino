#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"


uint8_t crates[127];

int main(void){
	init();
	uint8_t x = 2;
	for (uint8_t i = 0; i < 102; i++){
		while ((x & 0x0F) > 0x0C || ((x & 0x0F) % 2 == 1 && ((x & 0xF0) >> 4) % 2 == 1)){
			x++;
		}
		crates[i] = x;
		x++;
	}

	DisplayOn();
	DisplayGame(crates, 0x00, 0xCC);

	while (1){
		//UpdateGame(crates, 0x01, 0xCC);
	}

	return 0;
	// feature
}