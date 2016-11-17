#include <MI0283QT9.h>
#include <Arduino.h>


#ifndef BasicDisplay
#define BasicDisplay

void DisplayOn();
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location);
void UpdateGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location);

void _displayBorder();
void _displayInnerStatic();
void _displayCrates(uint8_t crates[]);
void _displayPlayer(int_least16_t position, uint16_t playerColor);
void _displayInfo();

#endif