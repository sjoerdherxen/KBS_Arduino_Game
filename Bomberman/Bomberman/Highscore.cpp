#include "Highscore.h"

void Highscore(){
	while (1){
		//_delay_ms(10);

		//DisplayHighscore();
		// nunchuck read
		//uint8_t value = Nunchuck_get_data();
		uint8_t value = 0;
		if (value & (1 << 7)){ // c button
			return;
		}
	}
}