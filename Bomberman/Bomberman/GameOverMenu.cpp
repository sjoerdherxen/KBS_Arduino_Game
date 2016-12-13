#include "GameOverMenu.h"

void gameOverMenu() {
	setGameover(1);
	while (1) {
		DisplayGameOverMenu(0);
		delay(5000);
		DisplayGameOverMenu(1);
		delay(5000);
		DisplayGameOverMenu(2);
		delay(5000);
	}
}