#include "MainMenu.h"

// het hoofdmenu maken en tonen.
// geeft 1 terug als start starten is gekozen
// geeft 2 terug als highscores is gekozen
uint8_t Mainmenu(){

	uint8_t currentDisplay = 0;
	while (1){
		_delay_ms(10);
		DisplayMainMenu(currentDisplay);
		if (currentDisplay == 0){
			currentDisplay = 3;
		}
		// nunchuck read
		uint8_t value = Nunchuck_get_data();

		if ((value << 2) >> 2 == 3){// down
			currentDisplay = 2;
		}
		else if ((value << 2) >> 2 == 1){//up
			currentDisplay = 1;
		}
		if (value & (1 << 6)){ // z button
			if (currentDisplay == 1 || currentDisplay == 2){
				return currentDisplay;
			}
		}
	}
}