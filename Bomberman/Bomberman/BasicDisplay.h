#include <MI0283QT9.h>
#include <Arduino.h>


#ifndef BasicDisplay
#define BasicDisplay

void DisplayOn();
void DisplayGame();
void UpdateGame();

void _displayBorder();
void _displayInnerStatic();
void _displayCrates();
void _displayPlayer(int_least16_t position, uint16_t playerColor);
void _displayInfo();

#endif