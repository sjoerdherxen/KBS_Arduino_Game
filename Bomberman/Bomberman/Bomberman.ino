#include "score.h"
#include "Keyboard.h"

#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

int main(void) {
	init();
	//initIrSend();
	Serial.begin(9600);
	//GameInit();

	DisplayOn();
	setupPot();
	setupSpeaker();

	Nunchuck_setpowerpins();
	Nunchuck_init();

	// ports leds levens instellen
	setupExpander();

	gameOverMenu();


	return 1;
}

