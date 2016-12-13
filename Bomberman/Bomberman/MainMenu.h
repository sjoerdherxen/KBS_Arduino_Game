#include <Arduino.h>
#include "BasicDisplay.h"
#include "Nunchuck.h"
#include "soundEffects.h"
#include "Game.h"
//#include "IrComm.h"

#ifndef MainMenu
#define MainMenu

int ifStartMusic = 0;

/* function used to get the gametick */
void mainMenuTick(uint16_t count);

/* function used to show the main menu, it returns
the value of the menu item that is selected */
uint8_t Mainmenu();

#endif