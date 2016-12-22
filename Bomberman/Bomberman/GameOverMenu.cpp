#include "GameOverMenu.h"

uint8_t gameOverMenu() {
	uint8_t currentDisplay = 0;
	while (1) {
		_delay_ms(100);

		DisplayGameOverMenu(currentDisplay);

		if (currentDisplay == 0) {
			currentDisplay = 3;
		}

		uint8_t value = Nunchuck_get_data();
		if (value == 3) {
			currentDisplay = 2;
		}
		else if (value == 1) {
			currentDisplay = 1;
		}
		if (value & (1 << 6)) {
			if (currentDisplay == 1 || currentDisplay == 2) {
				return currentDisplay;
			}
		}
	}
}