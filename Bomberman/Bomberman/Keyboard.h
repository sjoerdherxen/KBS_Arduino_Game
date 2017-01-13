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

/* This function is used to select the different characters with the nunchuck*/
char* selectChars(MI0283QT9 *scherm);

/*Draws the middle 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
/*And it also gets the color, if it is selected it will need to set the green selected color and otherwise it needs the white color*/
void drawLetter(uint8_t selected, MI0283QT9 *scherm, char *letter, uint8_t color);

/*Draws the upper 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
void drawUpper(uint8_t selected, MI0283QT9 *scherm, char *letter);

/*Draws the lower 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
void drawLower(uint8_t selected, MI0283QT9 *scherm, char *letter);

#endif