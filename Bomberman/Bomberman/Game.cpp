#include "Game.h"

uint8_t *crates;
volatile uint8_t gameTickReady;
uint8_t player1Location = 0x00;
uint8_t player2Location = 0xCC;

void GameTick(uint16_t count){
	if (count % 3 == 1){
		uint8_t nunchuck = Nunchuck_get_data();
		uint8_t direction = (nunchuck << 2) >> 2;
		uint8_t oldpl1Loc = player1Location;
		PlayerMove(direction);

		UpdateGame(crates, crates, oldpl1Loc, player1Location, player2Location, player2Location);
	}
}

void Game(){
	crates = GenerateCrates();
	DisplayGame(crates, player1Location, player2Location);

	// set timer voor gametick
	uint16_t i = 0;
	while (1){
		if (1){
			GameTick(i++);
			_delay_ms(100);
		}
	}
}

void GameInit(){
	DisplayOn();

	Nunchuck_setpowerpins();
	Nunchuck_init();

	uint8_t selected = Mainmenu();

	if (selected == 1){ // start game
		Game();
	}
	else if (selected == 2){
		// todo highscore
		return;
	}
}

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
	if ((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1){
		newLocation = player1Location;
	}
	else {
		for (uint8_t i = 0; i < 127; i++){
			if (crates[i] == newLocation){
				newLocation = player1Location;
				break;
			}
		}
		if (newLocation == player2Location){
			newLocation = player1Location;
		}
	}


	player1Location = newLocation;
}

