#include "BasicDisplay.h"
#include <Arduino.h>
#include "Nunchuck.h"
#include "Crates.h"
#include "MainMenu.h"

#ifndef Game_h
#define Game_h

void GameTick(uint16_t count);
void Game();
void GameInit();
void PlayerMove(uint8_t direction);

#endif