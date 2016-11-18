#include "BasicDisplay.h"

MI0283QT9 scherm;

void DisplayOn(){
	scherm.begin();
	scherm.led(40);
	scherm.fillScreen(RGB(255, 255, 255));
}


void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location){
	_displayBorder();
	_displayInnerStatic();
	_displayCrates(crates);
	_displayInfo();
	_displayPlayer(player1Location, RGB(255, 0, 0));
	_displayPlayer(player2Location, RGB(0, 0, 255));
}
void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew){
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
	/*for (uint8_t i = 3; i < 12; i += 2){
		for (uint8_t j = 1; j < 14; j++){
		scherm.drawLine(81 + i * 16, 1 + j * 16, 95 + i * 16, 1 + j * 16, RGB(0, 0, 0));
		scherm.drawLine(81 + i * 16, 4 + j * 16, 95 + i * 16, 4 + j * 16, RGB(0, 0, 0));
		scherm.drawLine(81 + i * 16, 7 + j * 16, 95 + i * 16, 7 + j * 16, RGB(0, 0, 0));
		scherm.drawLine(81 + i * 16, 10 + j * 16, 95 + i * 16, 10 + j * 16, RGB(0, 0, 0));
		scherm.drawLine(81 + i * 16, 13 + j * 16, 95 + i * 16, 13 + j * 16, RGB(0, 0, 0));
		}
		}*/
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
	uint8_t x = ((square & 0xF0) >> 4) * 16;
	uint8_t y = 17 + (square & 0x0F) * 16;
	scherm.fillRect(96 + ((square & 0xF0) >> 4) * 16, 16 + (square & 0x0F) * 16, 16, 16, RGB(255, 255, 255));
}