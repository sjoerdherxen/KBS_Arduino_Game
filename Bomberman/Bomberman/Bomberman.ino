#include "score.h"

#include "Textures.h"
#include "BasicDisplay.h"
#include "Game.h"

int main(void) {
	init();
	Serial.begin(9600);

	GameInit();


	return 1;
}

