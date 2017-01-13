#include "BasicDisplay.h"
#include "Game.h"

MI0283QT9 scherm;
uint8_t SDcardLoaded = 0;
extern uint8_t player1Location;
extern uint8_t player2Location;
extern uint16_t player1Score;
extern uint16_t player2Score;
extern uint8_t player1Lives;
extern uint8_t player2Lives;

/* function to display bombs on the playing field */
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint16_t count) {

	/* for-loop to loop through all the bombs */
	for (uint16_t i = 0; i < 6; i++) {

		/* the function only works if the called bomb is a bomb */
		if (bombs[i]) {

			/* if the bomb is visible */
			if ((bombs[i] & 0x1F) < 0x18) {

				/* clear the square where the bomb is placed */
				_clearSquare(bombs[i] >> 8);

				/* if the SD-card is inserted, draw the texture of the bomb */
				if (SDcardLoaded) {
					drawTexture(1, ((bombs[i] & 0xF000) >> 12) * 16 + 96, ((bombs[i] & 0x0F00) >> 8) * 16 + 16, &scherm);
				}

				/* if the SD-card is not inserted, draw the default texture of the bomb */
				else {
					scherm.drawCircle(((bombs[i] & 0xF000) >> 12) * 16 + 104, ((bombs[i] & 0x0F00) >> 8) * 16 + 24, 7, RGB(0, 0, 0));
				}
			}
			/* if the bomb explodes */
			else if ((bombs[i] & 0x1F) < 0x19) {
				/* make an explosion sound */
				playExplosion(count);

				/* clear the square where the bomb is placed, so the explosion can be drawn */
				_clearSquare(bombs[i] >> 8);

				/* display the explosion of the bomb */
				_displayExplode(bombs[i] >> 8, count, i);

				/* display the explosion of the bomb in all four directions */
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 1, crates, count, i);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -1, crates, count, i);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 16, crates, count, i);
				_explodeLoop(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -16, crates, count, i);
			}

			/* remove the explosion */
			else {
				_clearSquare(bombs[i] >> 8);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 1, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -1, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, 16, crates);
				_explodeLoopDone(((bombs[i] & 0x00C0) >> 4) - 1, bombs[i] >> 8, -16, crates);
				_displayPlayers();
			}
		}
	}
}

/* function to be used to start the lcd-screen */
void DisplayOn() {

	/* turn on the screen */
	scherm.begin();

	/* sets the brightness of the screen */
	scherm.led(40);

	/* fills the screen with a white color */
	scherm.fillScreen(RGB(255, 255, 255));
}


/* function which changes the brightness of the screen by using the poteniometer */
void DisplayScherpte(uint8_t x) {
	/* sets the brightness of the screen */
	scherm.led(x);
}

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayMainMenu(uint8_t selected) {
	/* when the screen opens for the first time, selected equals 0 */
	if (selected == 0) {
		/* fills the screen with a white color */
		scherm.fillScreen(RGB(255, 255, 255));
		scherm.fillRect(35, 15, 240, 26, RGB(255, 0, 0));
		scherm.drawText(40, 20, "BOMBERMAN!", RGB(255, 255, 255), RGB(0, 0, 0), 3);
		scherm.drawText(80, 80, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 120, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);

		/* displays help text in the main menu */
		_displayMenuHelpers(2);
	}

	/* if "Start Game" is selected the 'selected' visuals will show */
	if (selected == 1) {
		scherm.drawRect(79, 79, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 119, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 80, "Start Game", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		scherm.drawText(80, 120, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	/* if "Highscores" is selected the 'selected' visuals will show */
	else if (selected == 2) {
		scherm.drawRect(79, 119, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 79, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 80, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 120, "Highscores", RGB(255, 255, 255), RGB(0, 0, 0), 2);
	}

	/* if nothing is selected the main menu will show as normal */
	else {
		scherm.drawRect(79, 79, 162, 18, RGB(255, 255, 255));
		scherm.drawRect(79, 119, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 80, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 120, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayGameOverMenu(uint8_t selected, uint8_t isNewHighscore) {
	if (isNewHighscore) {
		if (selected == 0) {
			/* fills the screen with a white color */
			scherm.fillScreen(RGB(255, 255, 255));

			/* displays Game Over! on the screen */
			scherm.drawText(40, 15, "Game Over!", RGB(0, 0, 0), RGB(255, 255, 255), 3);
			scherm.drawText(70, 90, "Your score: ", RGB(0, 0, 0), RGB(255, 255, 255), 2);
			scherm.drawInteger(252, 90, (unsigned long)player1Score, 10, RGB(0, 0, 0), RGB(255, 255, 255), 2);

			/* Main menu is the first selected button*/
			scherm.drawText(85, 41, "Main Menu", RGB(255, 255, 255), RGB(0, 0, 0), 2);

			/* displays help text in the main menu */
			_displayMenuHelpers(2);
		}

		/* if "Start Game" is selected the 'selected' visuals will show */
		if (selected == 1) {
			scherm.drawRect(84, 40, 145, 18, RGB(0, 0, 0));
			scherm.drawRect(79, 59, 162, 18, RGB(255, 255, 255));
			scherm.drawText(85, 41, "Main Menu", RGB(255, 255, 255), RGB(0, 0, 0), 2);

			scherm.drawText(80, 60, "Save Score", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		}

		/* if "Highscores" is selected the 'selected' visuals will show */
		else if (selected == 2) {
			scherm.drawRect(79, 59, 162, 18, RGB(0, 0, 0));
			scherm.drawRect(84, 40, 145, 18, RGB(255, 255, 255));
			scherm.drawText(85, 41, "Main Menu", RGB(0, 0, 0), RGB(255, 255, 255), 2);
			scherm.drawText(80, 60, "Save Score", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		}

		/* if nothing is selected the main menu will show as normal */
		else {
			scherm.drawRect(84, 40, 145, 18, RGB(255, 255, 255));
			scherm.drawRect(79, 59, 162, 18, RGB(255, 255, 255));
			scherm.drawText(85, 41, "Main Menu", RGB(0, 0, 0), RGB(255, 255, 255), 2);
			scherm.drawText(80, 60, "Save Score", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		}

		for (uint8_t i = 0; i < 3; i++) {
			for (uint8_t x = 10 + i * 3; x < i * 3 + 13; x++) {
				scherm.drawChar(80 + (x - (10 + i * 3)) * 16, 140 + i * 21, (char)getName(x), RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
			}
		}

		/* print every score */
		for (uint8_t i = 0; i < 3; i++) {
			uint8_t a = i * 2;
			scherm.drawInteger(192, 141 + i * 21, getScore(a), 10, RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
		}
	}
	else {
		if (selected == 0) {
			/* fills the screen with a white color */
			scherm.fillScreen(RGB(255, 255, 255));

			/* displays Game Over! on the screen */
			scherm.drawText(40, 15, "Game Over!", RGB(0, 0, 0), RGB(255, 255, 255), 3);
			scherm.drawText(70, 90, "Your score: ", RGB(0, 0, 0), RGB(255, 255, 255), 2);
			scherm.drawInteger(252, 90, (unsigned long)player1Score, 10, RGB(0, 0, 0), RGB(255, 255, 255), 2);

			scherm.drawText(80, 108, "Not a new highscore :(", RGB(255, 0, 0), RGB(255, 255, 255), 1);

			/* Main menu is the first selected button*/
			scherm.drawText(85, 51, "Main Menu", RGB(255, 255, 255), RGB(0, 0, 0), 2);

			/* displays help text in the main menu */
			_displayMenuHelpers(2);
		}

		/* if "Start Game" is selected the 'selected' visuals will show */
		if (selected == 1) {
			scherm.drawText(85, 51, "Main Menu", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		}

		/* print every name */
		for (uint8_t i = 0; i < 3; i++) {
			for (uint8_t x = 10 + i * 3; x < i * 3 + 13; x++) {
				scherm.drawChar(100 + (x - (10 + i * 3)) * 16, 141 + i * 21, (char)getName(x), RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
			}
		}

		/* print every score */
		for (uint8_t i = 0; i < 3; i++) {
			uint8_t a = i * 2;
			scherm.drawInteger(172, 141 + i * 21, getScore(a), 10, RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
		}
	}
}

/* display the game for the first time */
void DisplayGame(uint8_t crates[]){
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

	/* displays players */
	_displayPlayers();
}

/* function to display updates in the game */
void UpdateGame(uint8_t crates[], uint8_t player1LocationOld, uint8_t player2LocationOld, uint16_t *bombs, uint16_t count){
	/* display an updated crate */

	/* if player 1 has been moved since the last update, the player is drawn at it's new location */
	if (player1Location != player1LocationOld || player2Location != player2LocationOld){
		/* clear the square of the last posion of the player */
		_clearSquare(player1LocationOld);
		_clearSquare(player2LocationOld);

		/* draw a player */
		_displayPlayers();
	}

	/* if player 2 has been moved since the last update, the player is drawn at it's new location */
	_displayBombs(bombs, crates, count);
	_displayInfo();
}

/* function to display highscores */
void DisplayHighscore() {

	/* print the text "Highscores" */
	scherm.fillScreen(RGB(255, 255, 255));
	scherm.drawText(80, 20, "Highscores", RGB(0, 150, 0), RGB(255, 255, 255), 2);

	/* print every name */
	char name[10];
	for (uint8_t i = 0; i < 3; i++) {
		uint8_t b = 0;
		for (uint8_t x = 10 + i * 3; x < i * 3 + 13; x++) {
			scherm.drawChar(80 + (x-(10+i*3))*16, 41 + i * 21, (char)getName(x), RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
		}
	}

	/* print every score */
	for (uint8_t i = 0; i < 3; i++) {
		uint8_t a = i * 2;
		scherm.drawInteger(192, 41 + i * 21, getScore(a), 10, RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
	}

	/* display the info text for the menu */
	_displayMenuHelpers(1);
	while (1){
		uint8_t nunchuck = Nunchuck_get_data();
		if (nunchuck & (1 << 7)){
			__asm volatile ("  jmp 0");
		}
		_delay_ms(100);
	}
}

/* function to display the screen that is shown when the game is starting */
void DisplayStartingGame(){
	scherm.fillScreen(RGB(255, 255, 255));
#if IsMasterGame == 1
	/* print the text "Starting game" */
	scherm.drawText(56, 45, "Starting game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
#else
	/* print the text "Waiting on master" */
	scherm.drawText(24, 45, "Waiting on master", RGB(0, 0, 0), RGB(255, 255, 255), 2);
#endif
}

/* function to draw the border of the game */
void _displayBorder(){
	/* for every block in the length of 15 blocks */
	for (uint8_t i = 0; i < 15; i++) {

		/* for every block in the height of 15 blocks */
		for (uint8_t j = 0; j < 15; j++) {

			/* if the block is equal to the blocks on the side of the playing field */
			if (i == 0 || i == 14 || j == 0 || j == 14) {

				/* if the SD-card is inserted, the textures are loaded */
				if (SDcardLoaded) {
					drawTexture(3, 80 + i * 16, j * 16, &scherm);
				}

				/* if the SD-card is not inserted, the default textures are used */
				else {

					/* rectagles are drawn as default texture */
					scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
					scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
				}
			}
		}
	}
}

/* Show a loading-bar for the crates being send by IR */
void ShowLoader(uint8_t progress){
	/* show an empty loader if the progress starts */
	if (!progress){
		scherm.drawRect(93, 100, 125, 20, RGB(0, 0, 0));
	}
	/* add an expanding rectangle for the progress made */
	else {
		scherm.fillRect(91 + progress, 100, 3, 20, RGB(0, 0, 0));
	}
}

/* function to display the static blocks inside the playing field */
void _displayInnerStatic() {
	/* for each posision inside the border */
	for (uint8_t i = 2; i < 13; i += 2) {

		/* for each posision inside the border */
		for (uint8_t j = 2; j < 13; j += 2) {

			/* if the SD-card is inserted, the textures are loaded */
			if (SDcardLoaded) {
				drawTexture(3, 80 + i * 16, j * 16, &scherm);
			}

			/* if the SD-card is not inserted, the default textures are used */
			else {
				/* rectagles are drawn as default texture */
				scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
				scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
			}
		}
	}
}

/* function to display the crates inside the playing field */
void _displayCrates(uint8_t crates[]) {
	/* for-loop to loop through all the possible crate locations */
	for (uint8_t i = 0; i < 127; i++) {

		if (crates[i] != 0xFF) {

			/* if the SD-card is inserted, the textures are loaded */
			if (SDcardLoaded) {
				drawTexture(2, (((crates[i] & 0xF0) >> 4) * 16) + 96, 16 + (crates[i] & 0x0F) * 16, &scherm);
			}

			/* if the SD-card is not inserted, the default textures are used */
			else {
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
void _displayPlayers(){

	/* if the SD-card is inserted, the player texture will be loaded */
	if (SDcardLoaded){
		drawTexture(5, 96 + ((player1Location & 0xF0) >> 4) * 16, 16 + (player1Location & 0x0F) * 16, &scherm);
		drawTexture(6, 96 + ((player2Location & 0xF0) >> 4) * 16, 16 + (player2Location & 0x0F) * 16, &scherm);
	}
	/* if the SD-card is not inserted, the default texture will be used (an X with the player color) */
	else {
		scherm.drawChar(97 + ((player1Location & 0xF0) >> 4) * 16, 16 + (player1Location & 0x0F) * 16, 'X', RGB(255, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawChar(97 + ((player2Location & 0xF0) >> 4) * 16, 16 + (player2Location & 0x0F) * 16, 'X', RGB(0, 0, 255), RGB(255, 255, 255), 2);
	}
}

/* function to display the countdown at the start of the game */
void _displayCountDown() {
	/* for-loop to cycle through the numbers of the countdown */
	for (int i = 5; i > 0; i--) {
		//Draw the countdown in the info menu (from 5 to 1)
		scherm.drawInteger(5, 80, (unsigned long)i, 10, RGB(255, 0, 0), RGB(255, 255, 255), 9);
		_delay_ms(1000);
	}

	/* remove the '1' (last countdown digit) in the info menu */
	scherm.drawChar(5, 80, '1', RGB(255, 255, 255), RGB(255, 255, 255), 9);

	/* display the text "GO" in the info menu */
	scherm.drawText(5, 80, "GO", RGB(0, 255, 0), RGB(255, 255, 255), 4);
	_delay_ms(1000);

	/* remove the "GO" in the info menu */
	scherm.drawText(5, 80, "GO", RGB(255, 255, 255), RGB(255, 255, 255), 4);
}

/* function to display player info at the left side of the game screen */
void _displayInfoStart(){

	/* display the player */
	scherm.drawChar(5, 5, 'X', RGB(255, 0, 0), RGB(255, 255, 255), 2);
	scherm.drawChar(5, 125, 'X', RGB(0, 0, 255), RGB(255, 255, 255), 2);

	/* display the lives */
	scherm.drawText(5, 22, "Levens", RGB(0, 0, 0), RGB(255, 255, 255), 1);
	scherm.drawText(5, 142, "Levens", RGB(0, 0, 0), RGB(255, 255, 255), 1);

	/* display the score */
	scherm.drawText(5, 47, "Score", RGB(0, 0, 0), RGB(255, 255, 255), 1);
	scherm.drawText(5, 167, "Score", RGB(0, 0, 0), RGB(255, 255, 255), 1);
}

/* function to show the score and power-ups of a player */
void _displayInfo(){
	/* display the lives of each player */
	scherm.drawInteger(5, 31, player1Lives, 10, RGB(255, 0, 0), RGB(255, 255, 255), 2);
	scherm.drawInteger(5, 151, player2Lives, 10, RGB(0, 0, 255), RGB(255, 255, 255), 2);

	/* display score info for player 1 */
	if (player1Score >= 1000){
		scherm.fillRect(69, 55, 11, 16, RGB(255, 255, 255));
	}
	else if (player1Score >= 100){
		scherm.fillRect(53, 55, 27, 16, RGB(255, 255, 255));
	}
	else if (player1Score >= 10){
		scherm.fillRect(37, 55, 43, 16, RGB(255, 255, 255));
	}
	else {
		scherm.fillRect(21, 55, 59, 16, RGB(255, 255, 255));
	}

	/* display score info for player 2 */
	if (player2Score >= 1000){
		scherm.fillRect(69, 175, 11, 16, RGB(255, 255, 255));
	}
	else if (player2Score >= 100){
		scherm.fillRect(53, 175, 27, 16, RGB(255, 255, 255));
	}
	else if (player2Score >= 10){
		scherm.fillRect(37, 175, 43, 16, RGB(255, 255, 255));
	}
	else {
		scherm.fillRect(21, 175, 59, 16, RGB(255, 255, 255));
	}

	/* display the scores */
	scherm.drawInteger(5, 55, player1Score, 10, RGB(255, 0, 0), RGB(255, 255, 255), 2);
	scherm.drawInteger(5, 175, player2Score, 10, RGB(0, 0, 255), RGB(255, 255, 255), 2);

}

/* function to clear a square in the playing field */
void _clearSquare(uint8_t square) {
	scherm.fillRect(96 + ((square & 0xF0) >> 4) * 16, 16 + (square & 0x0F) * 16, 16, 16, RGB(255, 255, 255));
}

/* function to display info text on the main menu */
void _displayMenuHelpers(uint8_t which) {

	/* display text that explains the C-button */
	if (which & (1 << 0)) {
		scherm.drawText(5, 219, "C back", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	/* display text that explains the Z-button */
	if (which & (1 << 1)) {
		scherm.drawText(187, 219, "Z select", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

/* function to display the explosion */
void _displayExplode(uint8_t location, uint16_t count, uint8_t bombI){
	/* check if the player is inside the explosion */
	if (player1Location == location){

		/* make the player lose a life, and play the lose-life sound from the speaker */
		player1Lives--;
		loseLife(count);
		startLoseLife(count);
		if (bombI < 3){
			if (player1Score < 50)
				player1Score = 0;
			else
				player1Score -= 50;
		}
		else{
			player2Score += 100;
		}
	}

	/* make the player lose a life (for player 2) */
	if (player2Location == location){
		player2Lives--;
		loseLife(count);
		if (bombI >= 3){
			if (player2Score < 50)
				player2Score = 0;
			else
				player2Score -= 50;
		}
		else{
			player1Score += 100;
		}
	}

	/* draw the explosion */
	if (SDcardLoaded) {
		drawTexture(10, ((location & 0xF0) >> 4) * 16 + 96, (location & 0x0F) * 16 + 16, &scherm);
	}

	/* if the SD-card is not inserted, draw the default texture of the explosion (a black tirangle) */
	else {
		scherm.fillTriangle(((location & 0xF0) >> 4) * 16 + 104, (location & 0x0F) * 16 + 17, ((location & 0xF0) >> 4) * 16 + 97, (location & 0x0F) * 16 + 31, ((location & 0xF0) >> 4) * 16 + 111, (location & 0x0F) * 16 + 31, RGB(0, 0, 0));
	}
}

/* function to display the explosion in different directions (up, down, right, left) */
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint16_t count, uint8_t bombI){

	/* for-loop to loop through the distance of the explosion */
	for (int8_t j = 1; j < max; j++) {

		/* the location that the explosion goes in, is put into an integer */
		uint8_t newLocation = location + j*mul;

		/* check if the location that has to be exploded, is a static block */
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)) {

			/* stop the explosion */
			return j;
		}

		/* for-loop to loop through all the crates */
		for (uint8_t u = 0; u < 127; u++) {

			/* check if the location that has to be exploded, is a crate */
			if (crates[u] == newLocation) {

				/* clear the possion of the crate */
				_clearSquare(newLocation);

				/* display the explosion on the location of the crate */
				_displayExplode(newLocation, count, bombI);

				/* remove the crate after the explosion */
				crates[u] = 0xFF;

				if (bombI < 3){
					player1Score += 5;
				}
				else {
					player2Score += 5;
				}

				/* stop the explosion */
				return j;
			}
		}

		/* clear the location of the explosion */
		_clearSquare(location + j*mul);

		/* display the explosion */
		_displayExplode(location + j*mul, count, bombI);
	}
}

/* function to be called when the explosion is done */
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates) {

	/* for-loop to loop through the distance of the explosion */
	for (int8_t j = 1; j < max; j++) {

		/* the location that the explosion goes in, is put into an integer */
		uint8_t newLocation = location + j*mul;

		/* check if the location that is exploded, was a static block */
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)) {

			/* stop reset */
			return;
		}

		/* for-loop to loop through all the crates */
		for (uint8_t u = 0; u < 127; u++) {

			/* check if the location that has to be exploded, is a crate */
			if (crates[u] == newLocation) {

				/* stop reset */
				return;
			}
		}
		/* clear the location of the explosion */
		_clearSquare(location + j*mul);
	}
}

/* function to display the keyboard to insert highscores */
void DisplayKeyboard() {
	/* Fill the screen with a white background*/
	scherm.fillScreen(RGB(255, 255, 255));

	/* Shows the menu helper "z select" */
	_displayMenuHelpers(2);

	/* Draws the first 3 letters in the middle row, the first letter has the selected color*/
	scherm.drawChar(80, 80, 'A', RGB(255, 255, 255), RGB(0, 150, 0), 4);
	scherm.drawChar(112, 80, 'A', RGB(255, 255, 255), RGB(0, 0, 0), 4);
	scherm.drawChar(144, 80, 'A', RGB(255, 255, 255), RGB(0, 0, 0), 4);

	/* Draws the first row top and bottom grey letters*/
	scherm.drawChar(80, 120, 'B', RGB(170, 170, 170), RGB(255, 255, 255), 4);
	scherm.drawChar(80, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);

	/* Draws the second row top and bottom grey letters*/
	scherm.drawChar(112, 120, 'B', RGB(170, 170, 170), RGB(255, 255, 255), 4);
	scherm.drawChar(112, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);

	/* Draws the third row top and bottom grey letters*/
	scherm.drawChar(144, 120, 'B', RGB(170, 170, 170), RGB(255, 255, 255), 4);
	scherm.drawChar(144, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);

	/* Draws the "confirm" text*/
	scherm.drawText(184, 90, "Confirm", RGB(0, 0, 0), RGB(255, 255, 255), 2);

	/*Starts the function showMiddle so the user can select characters*/
	selectChars(&scherm);
}