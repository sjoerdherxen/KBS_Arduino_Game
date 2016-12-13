#include <util/delay.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>
#include <wire.h>
#include <MI0283QT9.h>
#include "BasicDisplay.h"
#include "soundEffects.h"
#include "GameOverMenu.h"

#ifndef showLives

#define showLives
void setupExpander();
void blink(int check2);
void loseLife(uint16_t count);
void endOfGame(uint16_t count);
void startLives();

#endif // !showLives