#include "MainMenu.h"

int ifStartMusic = 0;

void mainMenuTick(uint16_t count) {
	if (ifStartMusic) {
		startMusic(count);
	}
}

/* function used to make the main menu and to display it,
it returns values of selected menu items */
uint8_t Mainmenu(){
	ifStartMusic = 1;

#if IsMasterGame == 1
	/* the currentdisplay variable is used to
	determine which	menu item is selected */
	uint8_t currentDisplay = 0;

	/* this loop keeps going on while in the main menu */
	while (1){
		/* a delay is used everytime the while-loop runs */
		_delay_ms(100);
		/* this displays the main menu itself */
		DisplayMainMenu(currentDisplay);
		if (currentDisplay == 0){
			/* if currentDisplay has the value 3, no menu item is selected,
			this is how the main menu starts up when the nunchuck has not
			been touched yet */
			currentDisplay = 3;
		}

		/* the nunchuck is read and the data is set into a variable */
		uint8_t value = Nunchuck_get_data();
		/* the value variable is read, the value determines which
		menu item is selected */
		if (value == 3){// down
			currentDisplay = 2;
		}
		else if (value == 1){//up
			currentDisplay = 1;
		}
		/* if the data of the nunchuck contains a press of the
		Z-button, the menu item which is selected will be pressed */
		if (value & (1 << 6)){
			if (currentDisplay == 1 || currentDisplay == 2){
				ifStartMusic = 0;
				return currentDisplay;
			}
		}

	}
#endif
#if IsMasterGame == 0

	// this is displayed on the secondaire arduino, it will say waiting for primary.
	DisplayMainMenu(0);
	while (1){

		if (dataAvailable()){
			return 1;
		}
	}
	return 0;
#endif
}

