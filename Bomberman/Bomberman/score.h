#include <Arduino.h>

#ifndef score
#define score

/* function used to setup the scores at the beginning of the game */
void setupScore();

/* function to add score to a specific player,
needs an amount for points and a target player*/
void addScore(uint8_t points, uint8_t player);

/* function used to return the score of a specific player */
uint8_t returnScore(int player);

#endif