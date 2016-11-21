#include <MI0283QT9.h>
#include <Arduino.h>


#ifndef BasicDisplay
#define BasicDisplay

void DisplayOn();
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location);
void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew);

void DisplayMainMenu(uint8_t selected);

void DisplayScherpte(uint8_t x);

void DisplayHighscore(char **names, uint8_t *scores);

void _displayBorder();
void _displayInnerStatic();
void _displayCrates(uint8_t crates[]);
void _displayPlayer(int_least16_t position, uint16_t playerColor);
void _displayInfo();
void _displayCrates(uint8_t oldCrates[], uint8_t newCrates[]);
void _clearSquare(uint8_t square);
void _displayMenuHelpers(uint8_t witch);

#endif