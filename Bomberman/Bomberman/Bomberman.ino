#include "score.h"

#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

int main(void) {
	init();
	//initIrSend();
	Serial.begin(9600);
	GameInit();

	while (1);

	delay(10);
	printHighscore();
	delay(10);
	//DisplayHighscore();
	return 1;
}

