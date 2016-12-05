#include "Game.h"

uint8_t *crates;
volatile uint8_t gameTickReady;
uint8_t player1Location = 0x00;
uint8_t player2Location = 0xCC;
uint16_t bombs[6];
uint8_t nextPlayerMove;
uint8_t screenBrightness = 0;


// dit is de code van een gametick. dit wordt 10x per seconde uitgevoerd.
// todo zorg ervoor dat timing via een timer/interupt werkt.
void GameTick(uint16_t count){

	uint8_t nunchuck = Nunchuck_get_data();

	uint8_t oldpl1Loc = player1Location;
	if (nextPlayerMove){
		nextPlayerMove--;
	}
	else {
		PlayerMove((nunchuck << 2) >> 2);
		if (oldpl1Loc != player1Location){
			nextPlayerMove = 1;
		}
	}
	if (nunchuck & 0x40){
		PlaceBomb();
	}

	UpdateBoms();

	UpdateGame(crates, crates, oldpl1Loc, player1Location, player2Location, player2Location, bombs);

	if (screenBrightness != setBrightness()){
		screenBrightness = setBrightness();
		DisplayScherpte(screenBrightness);
	}

}

// deze code is voor het initialseren van de game
void Game(){
	crates = GenerateCrates();
	// initiele weergave van spel
	DisplayGame(crates, player1Location, player2Location);

	// standaard spelwaarden zetten
	nextPlayerMove = 0;
	for (uint8_t i = 0; i < 6; i++){
		bombs[i] = 0;
	}

	// set timer voor gametick
	uint16_t i = 0;

	// led levens opstarten
	startLives();

	while (1){
		// verander timing naar timer/counter/interrupt
		GameTick(i++);
		_delay_ms(100);
	}

	
	
}

// dit wordt uitgevoerd bij het opstarten van de arduino
void GameInit(){
	// standaard items goedzetten
	DisplayOn();
	setupPot();
	screenBrightness = setBrightness();

	Nunchuck_setpowerpins();
	Nunchuck_init();

	// ports leds levens instellen
	//setupPorts();

	// testcode
	initIrSend();

	// hoofdmenu openen
	uint8_t selected = Mainmenu();

	if (selected == 1){ // start game
		Game();
	}
	else if (selected == 2){
		// todo highscore
		return;
	}
}

// beweeg de speler en check of nieuwe locatie een geldige locatie is
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
	// is statisch block
	if ((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1){
		newLocation = player1Location;
	}
	else {
		// is krat
		for (uint8_t i = 0; i < 127; i++){
			if (crates[i] == newLocation){
				newLocation = player1Location;
				break;
			}
		}
		// is andere speler hier
		if (newLocation == player2Location){
			newLocation = player1Location;
		}
	}

	player1Location = newLocation;
}

uint8_t returnPlayerLocation() {
	return player1Location;
}

// bom statussen updaten
void UpdateBoms(){
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