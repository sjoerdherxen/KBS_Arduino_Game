#ifndef score
#define score

void saveScore(uint16_t scorePlayer, uint8_t lttr1, uint8_t lttr2, uint8_t lttr3);

uint16_t getScore(uint16_t id);

void isHighscore(uint16_t current);

void resetScore();

void printHighscore();

#endif