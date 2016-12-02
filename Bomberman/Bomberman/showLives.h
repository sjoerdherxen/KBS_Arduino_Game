#include <util/delay.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>
#include <wire.h>
#include <MI0283QT9.h>
#include "BasicDisplay.h"


#ifndef showLives

#define showLives
void setupExpander();
void blink(int check2);
void loseLife();
void endOfGame();
void startLives();

#endif // !showLives