#include "GameOverMenu.h"

extern uint16_t player1Score;

uint8_t gameOverMenu() {
	uint8_t currentDisplay = 0;
	uint8_t value = Nunchuck_get_data();
	uint8_t isNewHighscore;
	isNewHighscore = 0;

	for (int i = 0; i < 5; i = i + 2) {
		Serial.println(player1Score);
		if (getScore(i) < player1Score) {
			isNewHighscore = 1;
		}
	}

	if (isNewHighscore) {
		Serial.println("Nieuwe highscore");
		while (1) {
			_delay_ms(100);

			DisplayGameOverMenu(currentDisplay, isNewHighscore);

			if (currentDisplay == 0) {
				currentDisplay = 3;
			}

			value = Nunchuck_get_data();
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
	else {
		Serial.println("Te lage score");
		while (1) {
			_delay_ms(100);

			DisplayGameOverMenu(currentDisplay, isNewHighscore);

			if (currentDisplay == 0) {
				currentDisplay = 1;
			}

			value = Nunchuck_get_data();

			if (value & (1 << 6)) {
				return currentDisplay;
			}
		}
	}
}