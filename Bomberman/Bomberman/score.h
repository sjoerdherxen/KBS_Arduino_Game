#ifndef score
#define score

void saveScore(uint16_t scorePlayer, uint16_t id);

uint16_t getScore(uint16_t id);

int isHighscore(uint16_t scorePlayer);

void resetScore();

#endif