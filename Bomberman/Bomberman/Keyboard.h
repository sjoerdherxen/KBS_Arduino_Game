#include <MI0283QT9.h>
#include <Arduino.h>
#include "Textures.h"
#include "score.h"
#include "Nunchuck.h"
#include "Game.h"

#define GREEN 150
#define WHITE 0


#ifndef Keyboard
#define Keyboard

void drawLetter(uint8_t selected, MI0283QT9 *scherm, char *letter, uint8_t color);
void drawUpper(uint8_t selected, MI0283QT9 *scherm, char *letter);
void drawLower(uint8_t selected, MI0283QT9 *scherm, char *letter);
char* showMiddle(MI0283QT9 *scherm);


#endif