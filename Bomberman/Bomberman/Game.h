#define IsMasterGame 1 // is the master or slave game 
#define UseTextures 0 // gebruik maken van textures uit sdkaart
#define Multiplayer 1 // enable multiplayer
#define IrCommUseTimer 0 // used for toggling between timer and delay version of sending data

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

void setGameover(int gameoverSet);
void GameTick(uint16_t count, int gameover);
void Game();
void GameInit();
void showMainMenu();
void PlayerMove(uint8_t direction);
uint8_t returnPlayerLocation();
void UpdateBombs();
uint16_t PlaceBomb();



#endif