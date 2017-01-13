#define IsMasterGame 1 // is the master or slave game 
#define UseTextures 0 // gebruik maken van textures uit sdkaart
#define Multiplayer 0// enable multiplayer
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

/* function to set the gameover value */
void setGameover(int gameoverSet);

/* function to generate the gametick, the gametick is called every 10th of a second */
void GameTick(uint16_t count, int gameover);

/* function to initialize the game */
void Game();

/* function to initialize the game on startup */
void GameInit();

/* function to show the main menu */
void showMainMenu();

/* function to move the player */
void PlayerMove(uint8_t direction);

/* function to return the player location */
uint8_t returnPlayerLocation();

/* function to update the bombs */
void UpdateBombs();

/* function to place a bomb by a player */
uint16_t PlaceBomb();

#endif