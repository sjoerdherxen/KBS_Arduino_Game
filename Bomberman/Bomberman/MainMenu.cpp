#include "MainMenu.h"

/* function used to make the main menu and to display it,
it returns values of selected menu items */
uint8_t Mainmenu(){

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
		if ((value << 2) >> 2 == 3){// down
			currentDisplay = 2;
		}
		else if ((value << 2) >> 2 == 1){//up
			currentDisplay = 1;
		}

		/* if the data of the nunchuck contains a press of the
		Z-button, the menu item which is selected will be pressed */
		if (value & (1 << 6)){
			if (currentDisplay == 1 || currentDisplay == 2){
				return currentDisplay;
			}
		}
	}
}