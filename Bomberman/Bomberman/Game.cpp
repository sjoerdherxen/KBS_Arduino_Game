#include "Game.h"

uint8_t *crates;
volatile uint8_t gameTickReady;
uint8_t player1Location = 0x00;
uint8_t player2Location = 0xCC;
uint16_t bombs[6];
uint8_t nextPlayerMove;
uint8_t screenBrightness = 0;

/* function to generate the gametick, the gametick is called every 10th of a second */
void GameTick(uint16_t count){

	/* insert the nunchuck data into an 8-bit integer */
	uint8_t nunchuck = Nunchuck_get_data();

	/* insert the location of the player into an 8-bit integer */
	uint8_t oldpl1Loc = player1Location;
	
	/* place a bomb */
	if (nunchuck & 0x40){
		PlaceBomb();
	}
	
	/* move the player */
	if (nextPlayerMove){
		nextPlayerMove--;
	}
	else {
		PlayerMove(nunchuck & 0x07);
		if (oldpl1Loc != player1Location){
			nextPlayerMove = 1;
		}
	}
	
	/* update the bombs on the playing field */
	UpdateBombs();

	/* update the game objects and players */
	UpdateGame(crates, crates, oldpl1Loc, player1Location, player2Location, player2Location, bombs, count);

	/* give the sounds a gametick so they can start playing when they are called */
	endOfGame(count);
	playLoseLife(count);
	playGameOver(count);
	playExplosion(count);

	mainMenuTick(count);
	playMusic(count);

	/* setting the brightness of the lcd-screen */
	if (screenBrightness != setBrightness()){
		screenBrightness = setBrightness();
		DisplayScherpte(screenBrightness);
	}

}

/* function to initialize the game */
void Game(){
	/* generate crates */
	crates = GenerateCrates();

	/* initial display of the game */
	DisplayGame(crates, player1Location, player2Location);

	/* set default game values */
	nextPlayerMove = 0;
	for (uint8_t i = 0; i < 6; i++){
		bombs[i] = 0;
	}

	/* set timer for the gametick */
	uint16_t i = 0;
	unsigned long prevGameTick = millis();

	/* start-up the leds so the lives can be shown */
	startLives();

	/* infinite loop for gametick */
	while (1){
		prevGameTick = millis();
		GameTick(i++);
		while (millis() < prevGameTick + 100);
	}
}

/* function to initialize the whole game at startup */
void GameInit(){

	/* setup functions for different aspects of the game */
	/* turn on the display */
	DisplayOn();

	/* setup for the potentiometer*/
	setupPot();

	/* setup for the speaker */
	setupSpeaker();

	/* setup for the brightness of the screen */
	screenBrightness = setBrightness();

	/* setup for the nunchuck */
	Nunchuck_setpowerpins();
	Nunchuck_init();

	/* setup for the port expander */
	setupExpander();

	/* open the main menu */
	_delay_ms(100);
	uint8_t selected = Mainmenu();

#if IsMasterGame == 1
	if (selected == 1){ // start game
		Game();
	}
	else if (selected == 2){
		// todo highscore
		return;
	}
#else
	Game();
#endif
}

// Move player to direction if valid newlocation
void PlayerMove(uint8_t direction){
	uint8_t newLocation = player1Location;

	switch (direction)
	{
	case 1: //up
		if ((player1Location & 0x0F) > 0){
			newLocation--;
		}
		break;
	case 2: // right
		if ((player1Location >> 4) < 12){
			newLocation += 0x10;
		}
		break;
	case 3: // down
		if ((player1Location & 0x0F) < 12){
			newLocation++;
		}
		break;
	case 4: //left
		if ((player1Location >> 4) > 0){
			newLocation -= 0x10;
		}
		break;
	}
	// is static block
	if ((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1){
		return;
	}

	// is crate
	for (uint8_t i = 0; i < 127; i++){
		if (crates[i] == newLocation){
			return;
		}
	}
	// is other player here
	if (newLocation == player2Location){
		return;
	}

	// is bomb
	for (uint8_t i = 0; i < 6; i++){
		if (bombs[i]){
			if ((bombs[i] & 0xFF00) >> 8 == newLocation){
				return;
			}
		}
	}


	player1Location = newLocation;
}

uint8_t returnPlayerLocation() {
	return player1Location;
}

// bom statussen updaten
void UpdateBombs(){
	for (uint8_t i = 0; i < 6; i++){
		if (bombs[i]){
			if ((bombs[i] & 0x001F) < 0x19){ // status ophogen
				bombs[i]++;
			}
			else { // bom resetten
				bombs[i] = 0;
			}
		}
	}
}

// een bom plaatsen door speler
void PlaceBomb(){
	if (!bombs[0]){
		bombs[0] = 0;
		bombs[0] |= (player1Location << 8) | 1 | (1 << 6);
	}
}