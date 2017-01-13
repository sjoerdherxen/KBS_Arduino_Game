#define IsMasterGame 1

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

/* function to generate the gametick, the gametick is called every 10th of a second */
void GameTick(uint16_t count);

/* function to initialize the game */
void Game();

/* function to initialize the whole game at startup */
void GameInit();
void PlayerMove(uint8_t direction);
uint8_t returnPlayerLocation();
void UpdateBombs();
void PlaceBomb();

#endif