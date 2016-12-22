#include <MI0283QT9.h>
#include <Arduino.h>

#ifndef score
#define score

/* function to save score for a specific name */
void saveScore(uint16_t scorePlayer, char name[]);

/* function to save the name of a player */
void saveName(uint8_t nameid, char name[]);

/* function to save a letter */
void saveLetter(uint8_t id, uint16_t letter);

/* function to get the score of a specific player id */
uint16_t getScore(uint16_t id);

/* function to get a name from an id */
uint16_t getName(uint16_t id);

/* function to get a name form an id, to display */
char getNameForDisplay(uint8_t id);

/* function to down grade the player name in the ranking */
void downGradeName(uint8_t id);

/* function used to see which ranking in the highscore a score belongs to */
void isHighscore(uint16_t current, char name[]);

/* function to reset the scores */
void resetScore();

/* function to print highscores */
void printHighscore();




#endif