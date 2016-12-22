#define IsMasterGame 1
#define UseTextures 0

#ifndef Game_h
#define Game_h
#include "BasicDisplay.h"
#include <Arduino.h>
#include "Nunchuck.h"
#include "Crates.h"
#include "MainMenu.h"
#include "Textures.h"
#include "ScreenBrightness.h"
#include "IrComm.h"
#include "showLives.h"
#include "soundEffects.h"

void GameTick(uint16_t count);
void Game();
void GameInit();
void PlayerMove(uint8_t direction);
uint8_t returnPlayerLocation();
void UpdateBombs();
uint16_t PlaceBomb();

#endif