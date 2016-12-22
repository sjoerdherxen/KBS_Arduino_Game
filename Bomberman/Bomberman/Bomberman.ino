#include "score.h"
#include "Keyboard.h"

#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

int main(void) {
	init();
	//initIrSend();
	Serial.begin(9600);
	//resetScore();
	/*
	saveScore(3, "JOR");
	saveScore(2, "IS ");
	saveScore(1, "GEY");
	*/
	//saveScore(9001, "OVR");
	//printHighscore();
	//GameInit();
	DisplayOn();
	DisplayKeyboard();
	while (1);



	return 1;
}

