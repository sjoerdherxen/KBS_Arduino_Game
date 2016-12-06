#include "BasicDisplay.h"
#include "Game.h"

MI0283QT9 scherm;
uint8_t SDcardLoaded = 0;

void DisplayOn(){
	// probeer de sdkaart te openen.
	SDcardLoaded = loadTextures();
	// scherm aanzetten.
	scherm.begin();
	scherm.led(40);
	scherm.fillScreen(RGB(255, 255, 255));
}


// helderheid van scherm aanpassen, wordt door potentiometer bepaalt.
void DisplayScherpte(uint8_t x){
	scherm.led(x);
}

// hoofdmenu tekenen
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

// spel voor eerste keer tonen.
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location){
	scherm.fillScreen(RGB(255, 255, 255)); // scherm resetten
	_displayBorder();
	_displayInnerStatic();
	_displayCrates(crates);
	_displayCountDown();
	_displayInfo();
	_displayPlayer(player1Location, RGB(255, 0, 0));
	_displayPlayer(player2Location, RGB(0, 0, 255));
}

// aanpassingen in game tonen op scherm
void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew, uint16_t *boms, uint16_t count){
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
	_displayBoms(boms, newCrates, player1LocationNew, count);
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

// de border van het spel tekenen
// word aan het begin van het spel getekend.
void _displayBorder(){
	for (uint8_t i = 0; i < 15; i++){
		for (uint8_t j = 0; j < 15; j++){
			if (i == 0 || i == 14 || j == 0 || j == 14){
				if (SDcardLoaded){
					drawTexture(3, 80 + i * 16, j * 16, &scherm);
				}
				else{
					scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
					scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
				}
			}
		}
	}
}

// de statische blokken in het speelveld tonen
// wordt aan begin van het spel getekend.
void _displayInnerStatic(){
	for (uint8_t i = 2; i < 13; i += 2){
		for (uint8_t j = 2; j < 13; j += 2){
			if (SDcardLoaded){
				drawTexture(3, 80 + i * 16, j * 16, &scherm);
			}
			else{
				scherm.fillRect(81 + i * 16, 1 + j * 16, 14, 14, RGB(0, 0, 0));
				scherm.drawRect(80 + i * 16, j * 16, 16, 16, RGB(100, 100, 100));
			}
		}
	}
}

// alle kratten tekenen 
// aan het begin van het spel wordt deze getekent.
void _displayCrates(uint8_t crates[]){
	for (uint8_t i = 0; i < 127; i++){
		if (crates[i] != 0xFF){

			if (SDcardLoaded){
				drawTexture(2, (((crates[i] & 0xF0) >> 4) * 16) + 96, 16 + (crates[i] & 0x0F) * 16, &scherm);
			}
			else{
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
}

// dit tekent de speler aan het begin van het spel.	
void _displayPlayer(int_least16_t position, uint16_t playerColor){
	if (SDcardLoaded){
		drawTexture(5, 96 + ((position & 0xF0) >> 4) * 16, 16 + (position & 0x0F) * 16, &scherm);
	}
	else {
		scherm.drawChar(97 + ((position & 0xF0) >> 4) * 16, 16 + (position & 0x0F) * 16, 'X', playerColor, RGB(255, 255, 255), 2);
	}
}

// dit zal de countdown afspelen aan het begin van het spel
void _displayCountDown() {
	for (int i = 5; i > 0; i--) { 
		//Draw the countdown in the info menu (from 5 to 1)
		scherm.drawInteger(5,80,(unsigned long)i,10, RGB(255, 0, 0), RGB(255, 255, 255), 9);
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

// dit tekend de kratten als deze aangepast wordt tijdens het spel. 
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

// reset een vakje
void _clearSquare(uint8_t square){
	scherm.fillRect(96 + ((square & 0xF0) >> 4) * 16, 16 + (square & 0x0F) * 16, 16, 16, RGB(255, 255, 255));
}

// menu helpers voor info over knoppen tonen.
void _displayMenuHelpers(uint8_t witch){
	if (witch & (1 << 0)){
		scherm.drawText(5, 219, "C back", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
	if (witch & (1 << 1)){
		scherm.drawText(187, 219, "Z select", RGB(0, 0, 0), RGB(255, 255, 255), 2);
	}
}

// de bommen tekenen die geplaatst zijn
void _displayBoms(uint16_t *boms, uint8_t *crates, uint8_t player1Location, uint16_t count){
	for (uint16_t i = 0; i < 6; i++){
		if (boms[i]){
			if ((boms[i] & 0x1F) < 0x18){ // bom is zichtbaar.
				_clearSquare(boms[i] >> 8);
				if (SDcardLoaded){
					drawTexture(1, ((boms[i] & 0xF000) >> 12) * 16 + 96, ((boms[i] & 0x0F00) >> 8) * 16 + 16, &scherm);
				}
				else{
					scherm.drawCircle(((boms[i] & 0xF000) >> 12) * 16 + 104, ((boms[i] & 0x0F00) >> 8) * 16 + 24, 7, RGB(0, 0, 0));
				}
			}
			else if ((boms[i] & 0x1F) < 0x19){ // bom explodeerd
				_clearSquare(boms[i] >> 8);
				_displayExplode(boms[i] >> 8);

				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 1, crates, player1Location, count);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -1, crates, player1Location, count);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 16, crates, player1Location, count);
				_explodeLoop(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -16, crates, player1Location, count);
			}
			else { // bom explosie weghalen.
				_clearSquare(boms[i] >> 8);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 1, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -1, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, 16, crates);
				_explodeLoopDone(((boms[i] & 0x00C0) >> 4) - 1, boms[i] >> 8, -16, crates);
			}
		}
	}
}

void _displayExplode(uint8_t location){ // teken bom explosie 
	if (SDcardLoaded){
		drawTexture(10, ((location & 0xF0) >> 4) * 16 + 96, (location & 0x0F) * 16 + 16, &scherm);
	}
	else {
		scherm.fillTriangle(((location & 0xF0) >> 4) * 16 + 104, (location & 0x0F) * 16 + 17, ((location & 0xF0) >> 4) * 16 + 97, (location & 0x0F) * 16 + 31, ((location & 0xF0) >> 4) * 16 + 111, (location & 0x0F) * 16 + 31, RGB(0, 0, 0));
	}
}

// explosie tekenen voor links rechts omhoog en omlaag.
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint8_t playerLoc, uint16_t count){
	for (int8_t j = 1; j < max; j++){
		uint8_t newLocation = location + j*mul;

		// check of statisch blok is
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){
			// stop de explosie
			return j;
		}

		// check of krat is
		for (uint8_t u = 0; u < 127; u++){
			if (crates[u] == newLocation){
				_clearSquare(newLocation);
				_displayExplode(newLocation);
				// haal krat weg en stop explosie hierna
				crates[u] = 0xFF;
				return j;
			}
		}

		// check of de speler in de explosie staat
		if (newLocation == playerLoc) {
			loseLife(count);
			startLoseLife(count);
		}

		// explosie verder tekenen.
		_clearSquare(location + j*mul);
		_displayExplode(location + j*mul);
	}
}

// explosie loop is klaar vergelijkbare code als functie hierboven
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates){
	for (int8_t j = 1; j < max; j++){
		uint8_t newLocation = location + j*mul;

		// is static
		if ((newLocation & 0x0F) > 0x0C ||
			(newLocation & 0xF0) > 0xC0 ||
			((newLocation & 0x0F) % 2 == 1 && ((newLocation & 0xF0) >> 4) % 2 == 1)){
			// stop reset
			return;
		}

		// is crate
		for (uint8_t u = 0; u < 127; u++){
			if (crates[u] == newLocation){
				// stop reset
				return;
			}
		}
		// maak vak wit.
		_clearSquare(location + j*mul);
	}
}