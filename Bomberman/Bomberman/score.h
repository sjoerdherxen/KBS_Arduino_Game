#ifndef score
#define score

void saveScore(uint16_t scorePlayer, uint16_t id);

uint16_t getScore(uint16_t id);

void isHighscore(uint16_t current);

void resetScore();

void printHighscore();

#endif