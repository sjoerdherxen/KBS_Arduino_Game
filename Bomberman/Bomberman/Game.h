#include "BasicDisplay.h"
#include <Arduino.h>
#include "Nunchuck.h"
#include "Crates.h"
#include "MainMenu.h"
#include "Textures.h"
#include "ScreenBrightness.h"
#include "IrComm.h"
#include "showLives.h"

#ifndef Game_h
#define Game_h

void GameTick(uint16_t count);
void Game();
void GameInit();
void PlayerMove(uint8_t direction);
uint8_t returnPlayerLocation();
void UpdateBombs();
void PlaceBomb();

#endif