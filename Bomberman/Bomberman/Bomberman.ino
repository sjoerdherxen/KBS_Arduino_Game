#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"


uint8_t crates[127];

int main(void){
	init();

	for (int i = 0; i < 127; i++){
		crates[i] = 0xFF;
	}
	for (uint8_t i = 0; i < 127; i++){
		crates[i] = 0x02;
	}

	DisplayOn();
	DisplayGame(crates, 0x00, 0xCC);

	while (1){
		UpdateGame(crates, 0x01, 0xCC);
	}

	return 0;
	// feature
}