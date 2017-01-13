#include <util/delay.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>
#include <wire.h>
#include <MI0283QT9.h>
#include "BasicDisplay.h"
#include "soundEffects.h"
#include "BasicDisplay.h"
#include "GameOverMenu.h"

#ifndef showLives

#define showLives

/* function used to setup the port expander */
void setupExpander();

/* function to turn on all leds, equal to a player having 5 full lives */
void startLives();

/* activates the blinking and after that the amount of leds equal to the amount of lives is set */
void loseLife(uint16_t count);

/* this is the animation the game will execute when a player is dead */
void endOfGame(uint16_t count);

#endif