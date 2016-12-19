#include <MI0283QT9.h>
#include <Arduino.h>
#include "Textures.h"

#ifndef BasicDisplay
#define BasicDisplay

void DisplayOn();
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location);
void UpdateGame(uint8_t crates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew, uint16_t *bombs, uint16_t count);
void DisplayStartingGame();

void DisplayMainMenu(uint8_t selected);

void DisplayScherpte(uint8_t x);

void DisplayHighscore(char **names, uint8_t *scores);

void ShowLoader(uint8_t progress);

void _displayBorder();
void _displayInnerStatic();
void _displayCrates(uint8_t crates[]);
void _displayPlayer(int_least16_t position, uint16_t playerColor);
void _displayInfo();
void _displayCountDown();
void _displayCrates(uint8_t oldCrates[], uint8_t newCrates[]);
void _clearSquare(uint8_t square);
void _displayMenuHelpers(uint8_t witch);
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint8_t player1Location, uint16_t count);
void _displayExplode(uint8_t location, uint8_t playerlocation, uint16_t count);
void _displayExplodeDone(uint8_t location);
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint8_t playerLoc, uint16_t count);
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates);


#endif