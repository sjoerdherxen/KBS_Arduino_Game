#include "GameOverMenu.h"

extern uint16_t player1Score;

/* function used to show the game-over menu, it returns the value of the menu item that is selected */
uint8_t gameOverMenu() {

	/* set values used in the game-over menu */
	uint8_t currentDisplay = 0;
	uint8_t value = Nunchuck_get_data();
	uint8_t isNewHighscore;
	isNewHighscore = 0;

	/* for loop to cycle through the scores */
	for (int i = 0; i < 5; i = i + 2) {
		if (getScore(i) < player1Score) {
			isNewHighscore = 1;
		}
	}

	/* check if there is a new highscore */
	if (isNewHighscore) {
		while (1) {
			_delay_ms(100);

			/* display the game-over menu */
			DisplayGameOverMenu(currentDisplay, isNewHighscore);

			if (currentDisplay == 0) {
				currentDisplay = 3;
			}

			/* get button presses from the nunchuck */
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
		while (1) {
			_delay_ms(100);

			/* display the game-over menu */
			DisplayGameOverMenu(currentDisplay, isNewHighscore);

			if (currentDisplay == 0) {
				currentDisplay = 1;
			}

			/* get the return button press from the nunchuck */
			value = Nunchuck_get_data();

			if (value & (1 << 6)) {
				return currentDisplay;
			}
		}
	}
}