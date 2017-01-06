#include <MI0283QT9.h>
#include <Arduino.h>
#include "Textures.h"
#include "score.h"

#ifndef BasicDisplay
#define BasicDisplay

void DisplayOn();
void DisplayGame(uint8_t crates[]);
void UpdateGame(uint8_t crates[], uint8_t player1LocationOld, uint8_t player2LocationOld, uint16_t *bombs, uint16_t count);

void DisplayMainMenu(uint8_t selected);

void DisplayGameOverMenu(uint8_t selected);

void DisplayScherpte(uint8_t x);

void DisplayHighscore();

void DisplayKeyboard();

void DisplayStartingGame();
void ShowLoader(uint8_t progress);

void _displayBorder();
void _displayInnerStatic();
void _displayCrates(uint8_t crates[]);
void _displayPlayers();
void _displayInfoStart();
void _displayInfo();
void _displayCountDown();
void _clearSquare(uint8_t square);
void _displayMenuHelpers(uint8_t witch);
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint16_t count);
void _displayExplode(uint8_t location, uint16_t count, uint8_t bombI);
void _displayExplodeDone(uint8_t location);
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint16_t count, uint8_t bombI);
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates);


#endif