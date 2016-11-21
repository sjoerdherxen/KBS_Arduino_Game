#include <util/delay.h>
#include <Arduino.h>

#ifndef showLives

#define showLives
void setupPorts();
void blink(int lives);
void loseLife(int *lifeCount);
void endOfGame();
void startLives();

#endif // !showLives
