#include "Game.h"

uint8_t *crates;
volatile uint8_t gameTickReady;
uint8_t player1Location = 0x00;
uint8_t player2Location = 0xCC;
uint16_t bombs[6];
uint8_t nextPlayerMove;
uint8_t screenBrightness = 0;
uint8_t player1Score = 0;
uint8_t player2Score = 0;


// dit is de code van een gametick. dit wordt 10x per seconde uitgevoerd.
// todo zorg ervoor dat timing via een timer/interupt werkt.
void GameTick(uint16_t count){

	uint8_t nunchuck = Nunchuck_get_data();

	uint8_t oldpl1Loc = player1Location;
	
	if (nunchuck & 0x40){
		PlaceBomb();
	}
	
	if (nextPlayerMove){
		nextPlayerMove--;
	}
	else {
		PlayerMove(nunchuck & 0x07);
		if (oldpl1Loc != player1Location){
			nextPlayerMove = 1;
		}
	}
	

	UpdateBombs();

	UpdateGame(crates, crates, oldpl1Loc, player2Location, bombs, count);

	endOfGame(count);
	playLoseLife(count);
	playGameOver(count);
	playExplosion(count);

	mainMenuTick(count);
	playMusic(count);

	if (screenBrightness != setBrightness()){
		screenBrightness = setBrightness();
		DisplayScherpte(screenBrightness);
	}

}

// deze code is voor het initialseren van de game
void Game(){
	crates = GenerateCrates();
	// initiele weergave van 
	DisplayGame(crates, player1Location, player2Location);

	// standaard spelwaarden zetten
	nextPlayerMove = 0;
	for (uint8_t i = 0; i < 6; i++){
		bombs[i] = 0;
	}

	// set timer voor gametick
	uint16_t i = 0;
	unsigned long prevGameTick = millis();
	// led levens opstarten
	startLives();

	while (1){
		prevGameTick = millis();
		GameTick(i++);
		while (millis() < prevGameTick + 100);
	}
}

// Executed on startup 
void GameInit(){
	// Setup
	DisplayOn();
	setupPot();
	setupSpeaker();
	screenBrightness = setBrightness();

	Nunchuck_setpowerpins();
	Nunchuck_init();

	// ports leds levens instellen
	setupExpander();

	// testcode
	//initIrSend();

	// hoofdmenu openen
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