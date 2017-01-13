#include <Arduino.h>

#ifndef score
#define score

/* function to save the score for a specific name */
void saveScore(uint16_t scorePlayer, char name[]);

/* function to save the name of a player */
void saveName(uint8_t nameid, char name[]);

/* function to save a letter */
void saveLetter(uint8_t id, uint16_t letter);

/* function to get the name for a specific id */
uint16_t getName(uint16_t id);

/* function to get the name for a specific id, used to display */
char getNameForDisplay(uint8_t id);

/* function used to down grade the name */
void downGradeName(uint8_t id);

/* function used to get the score for a specific id */
uint16_t getScore(uint16_t id);

/* function used to check if the achieved score fits into the highscore */
void isHighscore(uint16_t current, char name[]);

/* function to reset all scores */
void resetScore();

#endif