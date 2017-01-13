#include "Game.h"

uint8_t *crates;
volatile uint8_t gameTickReady;
#if IsMasterGame == 0
uint8_t player1Location = 0x00;
uint8_t player2Location = 0xCC;
#else 
uint8_t player1Location = 0xCC;
uint8_t player2Location = 0x00;
#endif
uint16_t bombs[6];
uint8_t nextPlayerMove;
uint8_t screenBrightness = 0;
uint16_t player1Score = 0;
uint16_t player2Score = 0;
uint8_t player1Lives = 5;
uint8_t player2Lives = 5;
int gameover = 0;

/* function to set the gameover value */
void setGameover(int gameoverSet) {
	gameover = gameoverSet;
}

/* function to generate the gametick, the gametick is called every 10th of a second */
void GameTick(uint16_t count, int gameover) {

	/* if the game is still running */
	if (!gameover) {

		/* insert the nunchuck data */
		uint8_t nunchuck = Nunchuck_get_data();

		/* insert the old player location */
		uint8_t oldpl1Loc = player1Location;

		/* place a bomb */
		uint16_t bomb = 0;
		if (nunchuck & 0x40){
			bomb = PlaceBomb();
		}

		/* cool down on player move */
		if (nextPlayerMove){
			nextPlayerMove--;
		}
		/* move the player */
		else {
			PlayerMove(nunchuck & 0x07);
			if (oldpl1Loc != player1Location) {
				nextPlayerMove = 1;
			}
		}

		/* place gameticks on the bombs */
		UpdateBombs();

		/* give the gametick to all the sounds */
		endOfGame(count);
		playLoseLife(count);
		playGameOver(count);
		playExplosion(count);

		/* set the screen brightness */
		if (screenBrightness != setBrightness()){
			screenBrightness = setBrightness();
			DisplayScherpte(screenBrightness);
		}

		uint8_t oldpl2Loc = player2Location;
#if Multiplayer == 1
#if IsMasterGame == 1
#if IrCommUseTimer
		sendTrippleStart(player1Location, ((bomb & 0xFF00) >> 8), (bomb & 0x00FF));
#else
		sendTripple(player1Location, ((bomb & 0xFF00) >> 8), (bomb & 0x00FF), 0);
		unsigned long start = millis();
		while (1){
			uint8_t *data = dataRecieve();
			if (data){
				player2Location = data[1];
				if (data[3] != 0){
					bombs[3] = 0;
					bombs[3] = data[3];
					bombs[3] |= ((uint16_t)data[2]) << 8;
				}
				break;
			}
			if (millis() - start > 200){
				break;
			}
		}
#endif
#else
#if IrCommUseTimer
		sendTrippleStart(player1Location, ((bomb & 0xFF00) >> 8), (bomb & 0x00FF));
#else
		unsigned long start = millis();
		while (1){
			uint8_t *data = dataRecieve();
			if (data){
				player2Location = data[1];
				if (data[3] != 0){
					bombs[3] = 0;
					bombs[3] = data[3];
					bombs[3] |= ((uint16_t)data[2]) << 8;
				}
				break;
			}
			if (millis() - start > 200){
				break;
			}
		}
		sendTripple(player1Location, ((bomb & 0xFF00) >> 8), (bomb & 0x00FF), 0);
#endif
#endif
#endif
		if (count % 10 == 9){
			player1Score++;
			player2Score++;
		}
		UpdateGame(crates, oldpl1Loc, oldpl2Loc, bombs, count);
	}
}

/* function to initialize the game */
void Game(){

	/* display the starting game */
	DisplayStartingGame();
	
	/* free all the crates */
	free(crates);

	/* generate the crates */
	crates = GenerateCrates();

	/* initial display of the crates */
	DisplayGame(crates);

	/* set default game values */
	nextPlayerMove = 0;
	for (uint8_t i = 0; i < 6; i++) {
		bombs[i] = 0;
	}

	/* set the timer for the gametick */
	uint16_t i = 0;
	unsigned long prevGameTick = millis();

	/* startup the led lives */
	startLives();
	_displayInfoStart();

	/* infinite loop for the gametick */
	while (1) {
		prevGameTick = millis();
		GameTick(i++, gameover);
		while (millis() < prevGameTick + 100);
	}
}

/* function to initialize the game on startup */
void GameInit() {
	
	/* turn on the display */
	DisplayOn();

	/* setup the potentiometer */
	setupPot();

	/* setup the infrared */
	setupIR();

	/* setup the speaker */
	setupSpeaker();

	/* setup the port expander */
	setupExpander();

	/* setup the nunchuck */
	setupNunchuck();

	/* show the main menu */
	showMainMenu();

}

/* function to show the main menu */
void showMainMenu() {
	
	/* set the gameover value to 0 to initialize the game as not done */
	setGameover(0);
	
	/* open the main menu */
	uint8_t selected = Mainmenu();

	/* start the game */
	if (selected == 1) {
		Game();
	}
	else if (selected == 2) {
		DisplayHighscore();
	}
}

/* function to move the player */
void PlayerMove(uint8_t direction) {
	uint8_t newLocation = player1Location;

	switch (direction)
	{
	/* move the player up */
	case 1:
		if ((player1Location & 0x0F) > 0) {
			newLocation--;
		}
		break;

	/* move the player right */
	case 2:
		if ((player1Location >> 4) < 12) {
			newLocation += 0x10;
		}
		break;

	/* move the player down */
	case 3:
		if ((player1Location & 0x0F) < 12) {
			newLocation++;
		}
		break;

	/* move the player left */
	case 4:
		if ((player1Location >> 4) > 0) {
			newLocation -= 0x10;
		}
		break;
	}

	/*check if it is a static block */
	if ((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1) {
		return;
	}

	/* check if it is a crate */
	for (uint8_t i = 0; i < 127; i++) {
		if (crates[i] == newLocation) {
			return;
		}
	}

	/* check if it is the other player */
	if (newLocation == player2Location) {
		return;
	}

	/* check if it is a bomb */
	for (uint8_t i = 0; i < 6; i++) {
		if (bombs[i]) {
			if ((bombs[i] & 0xFF00) >> 8 == newLocation) {
				return;
			}
		}
	}

	/* set a new player location */
	player1Location = newLocation;
}

/* function to return the player location */
uint8_t returnPlayerLocation() {
	return player1Location;
}

/* function to update the bombs */
void UpdateBombs() {
	for (uint8_t i = 0; i < 6; i++) {
		if (bombs[i]) {
			/* increase the state of the bombs */
			if ((bombs[i] & 0x001F) < 0x19) {
				bombs[i]++;
			}
			/* reste the bombs */
			else {
				bombs[i] = 0;
			}
		}
	}
}

/* function to place a bomb by a player */
uint16_t PlaceBomb(){
	if (!bombs[0]){
		bombs[0] = 0;
		bombs[0] |= (player1Location << 8) | 1 | (1 << 6);
		return bombs[0];
	}
	return 0;
}