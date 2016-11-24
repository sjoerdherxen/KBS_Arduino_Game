#include "BasicDisplay.h"

MI0283QT9 scherm;

void DisplayOn(){
	scherm.begin();
	scherm.led(40);
	scherm.fillScreen(RGB(255, 255, 255));
}

void DisplayScherpte(uint8_t x){
	scherm.led(x);
}

void DisplayMainMenu(uint8_t selected){
	if (selected == 0){ // scherm eerste keer openen
		scherm.fillScreen(RGB(255, 255, 255));
		_displayMenuHelpers(2);
	}
	if (selected == 1){ //start selected
		scherm.drawRect(79, 44, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 99, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(255, 255, 255), RGB(0, 0, 0), 2);
		scherm.drawText(80, 100, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
	else if (selected == 2){ // highscore selected
		scherm.drawRect(79, 99, 162, 18, RGB(0, 0, 0));
		scherm.drawRect(79, 44, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 100, "Highscores", RGB(255, 255, 255), RGB(0, 0, 0), 2);
	}
	else {// no selected
		scherm.drawRect(79, 44, 162, 18, RGB(255, 255, 255));
		scherm.drawRect(79, 99, 162, 18, RGB(255, 255, 255));
		scherm.drawText(80, 45, "Start Game", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawText(80, 100, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location){
	scherm.fillScreen(RGB(255, 255, 255));
	_displayBorder();
	_displayInnerStatic();
	_displayCrates(crates);
	_displayInfo();
	_displayPlayer(player1Location, RGB(255, 0, 0));
	_displayPlayer(player2Location, RGB(0, 0, 255));
}

void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew, uint16_t *boms){
	_displayCrates(oldCrates, newCrates);
	_displayInfo();
	if (player1LocationNew != player1LocationOld){
		_displayPlayer(player1LocationNew, RGB(255, 0, 0));
		_clearSquare(player1LocationOld);
	}
	if (player2LocationNew != player2LocationOld){
		_displayPlayer(player2LocationNew, RGB(0, 0, 255));
		_clearSquare(player2LocationOld);
	}
	_displayBoms(boms, newCrates);
}

void DisplayHighscore(char **names, uint8_t *scores){
	scherm.drawText(80, 20, "Highscores", RGB(0, 0, 0), RGB(255, 255, 255), 2);

	for (uint8_t i = 0; i < 5; i++){
		scherm.drawText(80, 41 + i * 21, names[i], RGB(0, 0, 0), RGB(255, 255, 255), 2);
		scherm.drawInteger(192, 41 + i * 21, (unsigned long)(scores[i]), 10, RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}

	_displayMenuHelpers(1);
}

void _displayBorder(){
	for (uint8_t i = 0; i < 15; i++){
		for (uint8_t j = 0; j < 15; j++){
			if (i == 0 || i == 14 || j == 0 || j == 14){
				scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
				scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
			}
		}
	}
}

void _displayInnerStatic(){
	for (uint8_t i = 2; i < 13; i += 2){
		for (uint8_t j = 2; j < 13; j += 2){
			scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
			scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
		}
	}
}

void _displayCrates(uint8_t crates[]){
	// todo set crates in random/preset locations
	for (uint8_t i = 0; i < 127; i++){
		if (crates[i] != 0xFF){
			uint8_t x1 = (((crates[i] & 0xF0) >> 4) * 16);
			uint8_t x2 = x1 + 14;
			uint8_t y = 17 + (crates[i] & 0x0F) * 16;

			scherm.drawLine((uint16_t)(x1)+97, y, (uint16_t)(x2)+97, y, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 3, (uint16_t)(x2)+97, y + 3, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 6, (uint16_t)(x2)+97, y + 6, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 9, (uint16_t)(x2)+97, y + 9, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 12, (uint16_t)(x2)+97, y + 12, RGB(0, 0, 0));
		}
	}
}

void _displayPlayer(int_least16_t position, uint16_t playerColor){
	scherm.drawChar(97 + ((position & 0xF0) >> 4) * 16, 16 + (position & 0x0F) * 16, 'X', playerColor, RGB(255, 255, 255), 2);
}

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

void _displayCrates(uint8_t oldCrates[], uint8_t newCrates[]){
	for (uint8_t i = 0; i < 127; i++){
		if (oldCrates[i] != 0xFF && oldCrates[i] != newCrates[i]){
			uint8_t x1 = (((newCrates[i] & 0xF0) >> 4) * 16);
			uint8_t x2 = x1 + 14;
			uint8_t y = 17 + (newCrates[i] & 0x0F) * 16;

			scherm.drawLine((uint16_t)(x1)+97, y, (uint16_t)(x2)+97, y, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 3, (uint16_t)(x2)+97, y + 3, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 6, (uint16_t)(x2)+97, y + 6, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 9, (uint16_t)(x2)+97, y + 9, RGB(0, 0, 0));
			scherm.drawLine((uint16_t)(x1)+97, y + 12, (uint16_t)(x2)+97, y + 12, RGB(0, 0, 0));

			_clearSquare(oldCrates[i]);
		}
	}
}

void _clearSquare(uint8_t square){
	scherm.fillRect(96 + ((square & 0xF0) >> 4) * 16, 16 + (square & 0x0F) * 16, 16, 16, RGB(255, 255, 255));
}

void _displayMenuHelpers(uint8_t witch){
	if (witch & (1 << 0)){
		scherm.drawText(5, 219, "C back", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
	if (witch & (1 << 1)){
		scherm.drawText(187, 219, "Z select", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

void _displayBoms(uint16_t *boms, uint8_t *crates){
	for (uint16_t i = 0; i < 6; i++){
		if (boms[i]){
			if ((boms[i] & 0x1F) < 0x18){
				_clearSquare(boms[i] >> 8);
				scherm.drawCircle(((boms[i] & 0xF000) >> 12) * 16 + 104, ((boms[i] & 0x0F00) >> 8) * 16 + 24, 7, RGB(0, 0, 0));
			}
			else if ((boms[i] & 0x1F) < 0x19){
				_clearSquare(boms[i] >> 8);
				_displayExplode(boms[i] >> 8);

				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 1, crates);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -1, crates);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 16, crates);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -16, crates);
			}
			else {
				_clearSquare(boms[i] >> 8);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 1, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -1, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 16, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -16, crates);
			}
		}
	}
}

void _displayExplode(uint8_t location){
	scherm.fillTriangle(((location & 0xF0) >> 4) * 16 + 104, (location & 0x0F) * 16 + 17, ((location & 0xF0) >> 4) * 16 + 97, (location & 0x0F) * 16 + 31, ((location & 0xF0) >> 4) * 16 + 111, (location & 0x0F) * 16 + 31, RGB(0, 0, 0));
}

int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates){
	for (int8_t j = 1; j < max; j++){
		uint8_t newLocation = location + j*mul;

		// is static
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){
			return j;
		}

		// is crate
		for (uint8_t u = 0; u < 127; u++){
			if (crates[u] == newLocation){
				_clearSquare(newLocation);
				_displayExplode(newLocation);
				crates[u] = 0xFF;
				return j;
			}
		}

		_clearSquare(location + j*mul);
		_displayExplode(location + j*mul);
	}
}

void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates){
	for (int8_t j = 1; j < max; j++){
		uint8_t newLocation = location + j*mul;

		// is static
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){
			return;
		}

		// is crate
		for (uint8_t u = 0; u < 127; u++){
			if (crates[u] == newLocation){
				return;
			}
		}
		_clearSquare(location + j*mul);
	}
}