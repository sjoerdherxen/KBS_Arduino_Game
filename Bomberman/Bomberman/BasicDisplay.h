#include <MI0283QT9.h>
#include <Arduino.h>
#include "Textures.h"

#ifndef BasicDisplay
#define BasicDisplay

/* function to display bombs on the playing field */
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint8_t player1Location, uint16_t count);

/* function to be used to start the lcd-screen */
void DisplayOn();

/* function which changes the brightness of the screen by using the poteniometer */
void DisplayScherpte(uint8_t x);

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayMainMenu(uint8_t selected);

/* display the game for the first time */
void DisplayGame(uint8_t crates[], uint8_t player1Location, uint8_t player2Location);

/* function to display updates in the game */
void UpdateGame(uint8_t oldCrates[], uint8_t newCrates[], uint8_t player1LocationOld, uint8_t player1LocationNew, uint8_t player2LocationOld, uint8_t player2LocationNew, uint16_t *bombs, uint16_t count);

/* highscores tonen verwacht 5 3 letterige namen. 5 scores. */
void DisplayHighscore(char **names, uint8_t *scores);

/* function to draw the border of the game */
void _displayBorder();

/* function to display the static blocks inside the playing field */
void _displayInnerStatic();

/* function to display the crates inside the playing field */
void _displayCrates(uint8_t crates[]);

/* function to draw the players at the beginning of the game */
void _displayPlayer(int_least16_t position, uint16_t playerColor);

/* this function will be executed when the game starts */
void _displayCountDown();

/* function to show the score and power-ups of a player */
void _displayInfo();

/* function to display crates once their updated */
void _displayCrates(uint8_t oldCrates[], uint8_t newCrates[]);

/* function to clear a square in the playing field */
void _clearSquare(uint8_t square);

/* function to display info text on the main menu */
void _displayMenuHelpers(uint8_t witch);

/* function to display the explosion of a bomb */
void _displayExplode(uint8_t location, uint8_t playerlocation, uint16_t count);

/* function to display the explosion in different directions (up, down, right, left) */
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint8_t playerLoc, uint16_t count);

/* function to be called when the explosion is done */
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates);

#endif