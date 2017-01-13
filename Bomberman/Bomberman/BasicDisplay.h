#include <MI0283QT9.h>
#include <Arduino.h>
#include "Textures.h"
#include "score.h"
#include "Keyboard.h"

#ifndef BasicDisplay
#define BasicDisplay

/* function to display bombs on the playing field */
void _displayBombs(uint16_t *bombs, uint8_t *crates, uint16_t count);

/* function to be used to start the lcd-screen */
void DisplayOn();

/* function which changes the brightness of the screen by using the poteniometer */
void DisplayScherpte(uint8_t x);

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayMainMenu(uint8_t selected);

/* function to draw the main menu, it needs a selected menu item to function */
void DisplayGameOverMenu(uint8_t selected, uint8_t isNewHighscore);

/* display the game for the first time */
void DisplayGame(uint8_t crates[]);

/* function to display updates in the game */
void UpdateGame(uint8_t crates[], uint8_t player1LocationOld, uint8_t player2LocationOld, uint16_t *bombs, uint16_t count);

/* function to display highscores */
void DisplayHighscore();

/* function to display the screen that is shown when the game is starting */
void DisplayStartingGame();

/* function to draw the border of the game */
void _displayBorder();

/* Show a loading-bar for the crates being send by IR */
void ShowLoader(uint8_t progress);

/* function to display the static blocks inside the playing field */
void _displayInnerStatic();

/* function to display the crates inside the playing field */
void _displayCrates(uint8_t crates[]);

/* function to draw the players at the beginning of the game */
void _displayPlayers();

/* function to display the countdown at the start of the game */
void _displayCountDown();

/* function to display player info at the left side of the game screen */
void _displayInfoStart();

/* function to show the score and power-ups of a player */
void _displayInfo();

/* function to clear a square in the playing field */
void _clearSquare(uint8_t square);

/* function to display info text on the main menu */
void _displayMenuHelpers(uint8_t witch);

/* function to display the explosion */
void _displayExplode(uint8_t location, uint16_t count, uint8_t bombI);

/* function to display the explosion in different directions (up, down, right, left) */
int8_t _explodeLoop(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates, uint16_t count, uint8_t bombI);

/* function to be called when the explosion is done */
void _explodeLoopDone(uint16_t max, uint16_t location, int8_t mul, uint8_t *crates);

/* function to display the keyboard to insert highscores */
void DisplayKeyboard();

#endif