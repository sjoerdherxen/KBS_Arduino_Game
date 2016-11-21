#include <Arduino.h>

#ifndef showLives

#define showLives
void setPorts();
void blink(int lives);
void loseLife(int *lifeCount);
void endOfGame();
int main();

#endif // !showLives
