#include <Arduino.h>
#include "BasicDisplay.h"
#include "Nunchuck.h"
#include "soundEffects.h"
#include "IrComm.h"

#ifndef MainMenu
#define MainMenu

// returns 1 for start game, 2 for highscores
/* function used to show the main menu, it returns
the value of the menu item that is selected */

uint8_t Mainmenu();

#endif