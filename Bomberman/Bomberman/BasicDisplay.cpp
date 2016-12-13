#include "BasicDisplay.h"
#include "Game.h"

MI0283QT9 scherm;
uint8_t SDcardLoaded = 0;

/* function to be used to start the lcd-screen */
void DisplayOn(){
	/* this tries to open the SD-card */
	SDcardLoaded = loadTextures();

	/* turn on the screen */
	scherm.begin();

	/* sets the brightness of the screen */
	scherm.led(40);

	/* fills the screen with a white color */
	scherm.fillScreen(RGB(255, 255, 255));
}


/* function which changes the brightness of the screen by using the poteniometer */
void DisplayScherpte(uint8_t x){
	/* sets the brightness of the screen */
	scherm.led(x);
}

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayMainMenu(uint8_t selected){
#if IsMasterGame == 1
	/* when the screen opens for the first time, selected equals 0 */
	if (selected == 0){
		/* fills the screen with a white color */
		scherm.fillScreen(RGB(255, 255, 255));

		/* displays help text in the main menu */
		_displayMenuHelpers(2);
	}

	/* if "Start Game" is selected the 'selected' visuals will show */
	if (selected == 1){
		scherm.drawRect(79, 44, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 99, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		scherm.drawText(80, 100, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	/* if "Highscores" is selected the 'selected' visuals will show */
	else if (selected == 2){
		scherm.drawRect(79, 99, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 44, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 100, "Highscores", RGB(255, 255, 255), RGB(0, 0, 0), 2);
	}

	/* if nothing is selected the main menu will show as normal */
	else {
		scherm.drawRect(79, 44, 162, 18, RGB(255, 255, 255));
		scherm.drawRect(79, 99, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 100, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
#endif
#if IsMasterGame == 0
	/* fills the screen with a white color */
	scherm.fillScreen(RGB(255, 255, 255));

	/* display "waiting for primary" */
	scherm.drawText(24, 45, "Waiting on master", RGB(0, 0, 0), RGB(255, 255, 255), 2);
#endif
}

/* display the game for the first time */
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location){
	/* reset the screen to a white color */
	scherm.fillScreen(RGB(255, 255, 255));

	/* the border of the playing field is drawn */
	_displayBorder();

	/* the static blocks of the playing field are drawn */
	_displayInnerStatic();

	/* the crates of the playing field are drawn */
	_displayCrates(crates);
	_displayCountDown();

	/* displays info about players */
	_displayInfo();

	/* displays player 1 */
	_displayPlayer(player1Location, RGB(255, 0, 0));

	/* displays player 2 */
	_displayPlayer(player2Location, RGB(0, 0, 255));
}

/* function to display updates in the game */
void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew, uint16_t *bombs, uint16_t count){
	/* display an updated crate */
	_displayCrates(oldCrates, newCrates);

	/* display the updated info */
	_displayInfo();

	/* if player 1 has been moved since the last update,
	the player is drawn at it's new location */
	if (player1LocationNew != player1LocationOld){
		/* draw a player */
		_displayPlayer(player1LocationNew, RGB(255, 0, 0));

		/* clear the square of the last posion of the player */
		_clearSquare(player1LocationOld);
	}

	/* if player 2 has been moved since the last update,
	the player is drawn at it's new location */
	if (player2LocationNew != player2LocationOld){
		/* draw a player */
		_displayPlayer(player2LocationNew, RGB(0, 0, 255));

		/* clear the square of the last posion of the player */
		_clearSquare(player2LocationOld);
	}

	/*  */
	_displayBombs(bombs, newCrates, player1LocationNew, count);
}

// highscores tonen verwacht 5 3 letterige namen. 5 scores.
void DisplayHighscore(char **names, uint8_t *scores){
	scherm.drawText(80, 20, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);

	for (uint8_t i = 0; i < 5; i++){
		scherm.drawText(80, 41 + i * 21, names[i], RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawInteger(192, 41 + i * 21, (unsigned long)(scores[i]), 10, RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	_displayMenuHelpers(1);
}

/* function to drawt the border of the game */
void _displayBorder(){
	/* for every block in the length of 15 blocks */
	for (uint8_t i = 0; i < 15; i++){

		/* for every block in the height of 15 blocks */
		for (uint8_t j = 0; j < 15; j++){

			/* if the block is equal to the blocks on the side of the playing field */
			if (i == 0 || i == 14 || j == 0 || j == 14){

				/* if the SD-card is inserted, the textures are loaded */
				if (SDcardLoaded){
					drawTexture(3, 80 + i * 16, j * 16, &scherm);
				}

				/* if the SD-card is not inserted, the default textures are used */
				else{
					/* rectagles are drawn as default texture */
					scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
					scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
				}
			}
		}
	}
}

/* function to display the static blocks inside the playing field */
void _displayInnerStatic(){
	/* for each posision inside the border */
	for (uint8_t i = 2; i < 13; i += 2){

		/* for each posision inside the border */
		for (uint8_t j = 2; j < 13; j += 2){

			/* if the SD-card is inserted, the textures are loaded */
			if (SDcardLoaded){
				drawTexture(3, 80 + i * 16, j * 16, &scherm);
			}

			/* if the SD-card is not inserted, the default textures are used */
			else{
				/* rectagles are drawn as default texture */
				scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
				scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
			}
		}
	}
}

/* function to display the crates inside the playing field */
void _displayCrates(uint8_t crates[]){
	/* for-loop to loop through all the possible crate locations */
	for (uint8_t i = 0; i < 127; i++){

		if (crates[i] != 0xFF){

			/* if the SD-card is inserted, the textures are loaded */
			if (SDcardLoaded){
				drawTexture(2, (((crates[i] & 0xF0) >> 4) * 16) + 96, 16 + (crates[i] & 0x0F) * 16, &scherm);
			}

			/* if the SD-card is not inserted, the default textures are used */
			else{
				uint8_t x1 = (((crates[i] & 0xF0) >> 4) * 16);
				uint8_t x2 = x1 + 14;
				uint8_t y = 17 + (crates[i] & 0x0F) * 16;

				/* to give the crate a little bit of default texture, lines are drawn */
				scherm.drawLine((uint16_t)(x1)+97, y, (uint16_t)(x2)+97, y, RGB(0, 0, 0));
				scherm.drawLine((uint16_t)(x1)+97, y + 3, (uint16_t)(x2)+97, y + 3, RGB(0, 0, 0));
				scherm.drawLine((uint16_t)(x1)+97, y + 6, (uint16_t)(x2)+97, y + 6, RGB(0, 0, 0));
				scherm.drawLine((uint16_t)(x1)+97, y + 9, (uint16_t)(x2)+97, y + 9, RGB(0, 0, 0));
				scherm.drawLine((uint16_t)(x1)+97, y + 12, (uint16_t)(x2)+97, y + 12, RGB(0, 0, 0));
			}
		}
	}
}
/* function to draw the players at the beginning of the game */
void _displayPlayer(int_least16_t position, uint16_t playerColor){

	/* if the SD-card is inserted, the player texture will be loaded */
	if (SDcardLoaded){
		drawTexture(5, 96 + ((position & 0xF0) >> 4) * 16, 16 + (position & 0x0F) * 16, &scherm);
	}
	/* if the SD-card is not inserted, the default texture will be used (an X with the player color) */
	else {
		scherm.drawChar(97 + ((position & 0xF0) >> 4) * 16, 16 + (position & 0x0F) * 16, 'X', playerColor, RGB(255, 255, 255), 2);
	}
}

// dit zal de countdown afspelen aan het begin van het spel
void _displayCountDown() {
	for (int i = 5; i > 0; i--) {
		//Draw the countdown in the info menu (from 5 to 1)
		scherm.drawInteger(5, 80, (unsigned long)i, 10, RGB(255, 0, 0), RGB(255, 255, 255), 9);
		_delay_ms(1000);
	}
	//Delete the 1 in the info menu
	scherm.drawChar(5, 80, '1', RGB(255, 255, 255), RGB(255, 255, 255), 9);
	//Draw GO in the info menu
	scherm.drawText(5, 80, "GO", RGB(0, 255, 0), RGB(255, 255, 255), 4);
	_delay_ms(1000);
	//Delete Go in the info menu
	scherm.drawText(5, 80, "GO", RGB(255, 255, 255), RGB(255, 255, 255), 4);
}
// dit zal de score en upgrades van de spelers tonen. 
/* function to show the score and power-ups of a player */
void _displayInfo(){
	// todo getplayercount

	scherm.drawChar(5, 5, 'X', RGB(255, 0, 0), RGB(255, 255, 255), 2);
	scherm.drawChar(5, 125, 'X', RGB(0, 0, 255), RGB(255, 255, 255), 2);

	// score:
	uint8_t pl1Score = 0;
	uint8_t pl2Score = 0;
	int i = 2;
	while (pl1Score > 0){
		scherm.drawInteger(27 + i * 16, 5, (long unsigned int)(pl1Score % 10), 10, RGB(255, 0, 0), RGB(255, 255, 255), 2);
		i--;
		pl1Score = pl1Score / 10;
	}
	i = 2;
	while (pl2Score > 0){
		scherm.drawInteger(27 + i * 16, 125, (long unsigned int)(pl2Score % 10), 10, RGB(0, 0, 255), RGB(255, 255, 255), 2);
		i--;
		pl2Score = pl2Score / 10;
	}
}

/* function to display crates once their updated */
void _displayCrates(uint8_t oldCrates[], uint8_t newCrates[]){

	/* for-loop to loop through each crate in the game */
	for (uint8_t i = 0; i < 127; i++){

		if (oldCrates[i] != 0xFF && oldCrates[i] != newCrates[i]){
			//uint8_t x1 = (((newCrates[i] & 0xF0) >> 4) * 16);
			//uint8_t x2 = x1 + 14;
			//uint8_t y = 17 + (newCrates[i] & 0x0F) * 16;

			///* to give the crate a little bit of default texture, lines are drawn */
			//scherm.drawLine((uint16_t)(x1)+97, y, (uint16_t)(x2)+97, y, RGB(0, 0, 0));
			//scherm.drawLine((uint16_t)(x1)+97, y + 3, (uint16_t)(x2)+97, y + 3, RGB(0, 0, 0));
			//scherm.drawLine((uint16_t)(x1)+97, y + 6, (uint16_t)(x2)+97, y + 6, RGB(0, 0, 0));
			//scherm.drawLine((uint16_t)(x1)+97, y + 9, (uint16_t)(x2)+97, y + 9, RGB(0, 0, 0));
			//scherm.drawLine((uint16_t)(x1)+97, y + 12, (uint16_t)(x2)+97, y + 12, RGB(0, 0, 0));

			_clearSquare(oldCrates[i]);
		}
	}
}

/* clear a square in the playing field */
void _clearSquare(uint8_t square){
	scherm.fillRect(96 + ((square & 0xF0) >> 4) * 16, 16 + (square & 0x0F) * 16, 16, 16, RGB(255, 255, 255));
}

/* function to display info text on the main menu */
void _displayMenuHelpers(uint8_t which){

	/* display text that explains the C-button */
	if (which & (1 << 0)){
		scherm.drawText(5, 219, "C back", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	/* display text that explains the Z-button */
	if (which & (1 << 1)){
		scherm.drawText(187, 219, "Z select", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

/* function to display bombs on the playing field */
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint8_t player1Location, uint16_t count){

	/* for-loop to loop through all the bombs */
	for (uint16_t i = 0; i < 6; i++){

		/* the function only works if the called bomb is a bomb */
		if (bombs[i]){

			/* if the bomb is visible */
			if ((bombs[i] & 0x1F) < 0x18){

				/* clear the square where the bomb is placed */
				_clearSquare(bombs[i] >> 8);

				/* if the SD-card is inserted, draw the texture of the bomb */
				if (SDcardLoaded){
					drawTexture(1, ((bombs[i] & 0xF000) >> 12) * 16 + 96, ((bombs[i] & 0x0F00) >> 8) * 16 + 16, &scherm);
				}

				/* if the SD-card is not inserted, draw the default texture of the bomb */
				else{
					scherm.drawCircle(((bombs[i] & 0xF000) >> 12) * 16 + 104, ((bombs[i] & 0x0F00) >> 8) * 16 + 24, 7, RGB(0, 0, 0));
				}
			}
			/* if the bomb explodes */
			else if ((bombs[i] & 0x1F) < 0x19){
				/* clear the square where the bomb is placed, so the explosion can be drawn */
				_clearSquare(bombs[i] >> 8);

				/* display the explosion of the bomb */
				_displayExplode(bombs[i] >> 8, player1Location, count);

				/* display the explosion of the bomb in all four directions */
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 1, crates, player1Location, count);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -1, crates, player1Location, count);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 16, crates, player1Location, count);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -16, crates, player1Location, count);
			}

			/* remove the explosion */
			else {
				_clearSquare(bombs[i] >> 8);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 1, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -1, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 16, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -16, crates);
			}
		}
	}
}

void _displayExplode(uint8_t location, uint8_t playerlocation, uint16_t count){
	// check of de speler in de explosie staat
	if (playerlocation == location){
		loseLife(count);
		startLoseLife(count);
	}

	// teken bom explosie
	if (SDcardLoaded){
		drawTexture(10, ((location & 0xF0) >> 4) * 16 + 96, (location & 0x0F) * 16 + 16, &scherm);

		// TODO: explosion animation
	}

	/* if the SD-card is not inserted, draw the default texture of the explosion (a black tirangle) */
	else {
		scherm.fillTriangle(((location & 0xF0) >> 4) * 16 + 104, (location & 0x0F) * 16 + 17, ((location & 0xF0) >> 4) * 16 + 97, (location & 0x0F) * 16 + 31, ((location & 0xF0) >> 4) * 16 + 111, (location & 0x0F) * 16 + 31, RGB(0, 0, 0));
	}
}

/* function to display the explosion in different directions (up, down, right, left) */
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint8_t playerLoc, uint16_t count){

	/* for-loop to loop through the distance of the explosion */
	for (int8_t j = 1; j < max; j++){

		/* the location that the explosion goes in, is put into an integer */
		uint8_t newLocation = location + j*mul;

		/* check if the location that has to be exploded, is a static block */
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){

			/* stop the explosion */
			return j;
		}

		/* for-loop to loop through all the crates */
		for (uint8_t u = 0; u < 127; u++){

			/* check if the location that has to be exploded, is a crate */
			if (crates[u] == newLocation){

				/* clear the possion of the crate */
				_clearSquare(newLocation);

				/* display the explosion on the location of the crate */
				_displayExplode(newLocation, playerLoc, count);

				/* remove the crate after the explosion */
				crates[u] = 0xFF;

				/* stop the explosion */
				return j;
			}
		}

		/* clear the location of the explosion */
		_clearSquare(location + j*mul);

		/* display the explosion */
		_displayExplode(location + j*mul, playerLoc, count);
	}
}

/* function to be called when the explosion is done */
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates){

	/* for-loop to loop through the distance of the explosion */
	for (int8_t j = 1; j < max; j++){

		/* the location that the explosion goes in, is put into an integer */
		uint8_t newLocation = location + j*mul;

		/* check if the location that is exploded, was a static block */
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){

			/* stop reset */
			return;
		}

		/* for-loop to loop through all the crates */
		for (uint8_t u = 0; u < 127; u++){

			/* check if the location that has to be exploded, is a crate */
			if (crates[u] == newLocation){

				/* stop reset */
				return;
			}
		}
		/* clear the location of the explosion */
		_clearSquare(location + j*mul);
	}
}