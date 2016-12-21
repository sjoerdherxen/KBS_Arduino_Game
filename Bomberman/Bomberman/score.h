#include <MI0283QT9.h>
#include <Arduino.h>

#ifndef score
#define score

void saveScore(uint16_t scorePlayer, char name[]);
void resetScore();

uint16_t getScore(uint16_t id);
uint16_t getName(uint16_t id);

void printHighscore();
char getNameForDisplay(uint8_t id);

void isHighscore(uint16_t current, char name[]);



#endif