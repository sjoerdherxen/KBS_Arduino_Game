#include "Keyboard.h"

extern uint16_t player1Score;

/* This function is used to select the different characters with the nunchuck*/
char* selectChars(MI0283QT9 *scherm) {

	/* The character/button which is selected by the nunchuck, 0 to 2 are the characters and 4 is the confirm button*/
	uint8_t selectedLetter = 0;

	/* Value is initialized and gets the nunchuck data*/
	uint8_t value = Nunchuck_get_data();

	/* An array for the characters is declared*/
	char letter[3];

	/* Adres 0, 1 and 2 get the starting value 'A' */
	for (int i = 0; i < 3; i++) {
		letter[i] = 'A';
	}

	/* The while loop starts and ends when confirm is pressed*/
	while (1) {

		/* Tick of 150 ms*/
		delay(150);

		/* Getting nunchuck data*/
		value = Nunchuck_get_data();

		/* If the nunchuck indicates it is pushing right*/
		if (value == 2) {

			/* Checks if it is not the most right button that was already selected so the selector won't go out of screen*/
			if (selectedLetter < 3) {

				/* The last character gets the unselected texture*/
				drawLetter(selectedLetter, scherm, letter, WHITE);
				selectedLetter++;

				/* The new selected character gets the selected texture*/
				drawLetter(selectedLetter, scherm, letter, GREEN);
			}
		}

		/* If the nunchuck indicates it is pushing left*/
		else if (value == 4) {

			/* Checks if it is not the most left button that was already selected*/
			if (selectedLetter > 0) {

				/* The last character gets the unselected texture*/
				drawLetter(selectedLetter, scherm, letter, WHITE);
				selectedLetter--;

				/* The new selected character gets the selected texture*/
				drawLetter(selectedLetter, scherm, letter, GREEN);
			}
		}

		/* Checks if the selector is actually selecting a letter*/
		if (selectedLetter <= 2) {

			/* Checks if the nunchuck is sending data that indicates it is pushing up*/
			if (value == 3) {
				/* The letter gets the new value*/
				letter[selectedLetter]++;
				/* This makes it so the keyboard will always be in the same loop and just start at the beginning again*/
				if (letter[selectedLetter] > 'Z') {
					letter[selectedLetter] = 'A';
				}
				/* Draws the new letters*/
				drawUpper(selectedLetter, scherm, letter);
				drawLetter(selectedLetter, scherm, letter, GREEN);
				drawLower(selectedLetter, scherm, letter);
			}
			/* Checks if the nunchuck is sending data that indicates it is pushing down*/
			else if (value == 1) {

				/* The letter gets the new value*/
				letter[selectedLetter]--;

				/* This makes it so the keyboard will always be in the same loop and just start at the beginning again*/
				if (letter[selectedLetter] < 'A') {
					letter[selectedLetter] = 'Z';
				}

				/* Draws the new letters*/
				drawUpper(selectedLetter, scherm, letter);
				drawLetter(selectedLetter, scherm, letter, GREEN);
				drawLower(selectedLetter, scherm, letter);
			}
		}
		else {

			/* The selector is selecting the confirm button*/
			scherm->drawText(184, 90, "Confirm", RGB(255, 255, 255), RGB(0, 0, 0), 2);

			/* If the Z button is pressed, go to the mainmenu and return the value of the name*/
			if (value & 0x40) {
				saveScore(player1Score, letter);
				delay(2000);
				__asm volatile ("  jmp 0");
				return letter;
			}
		}

		/* Checks if there is a character selected so the confirm button gets unselected*/
		if (selectedLetter < 3) {
			scherm->drawText(184, 90, "Confirm", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		}
	}
}

/*Draws the middle 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
/*And it also gets the color, if it is selected it will need to set the green selected color and otherwise it needs the white color*/
void drawLetter(uint8_t selected, MI0283QT9 *scherm, char *letter, uint8_t color) {
	switch (selected) {
	case 0:
		scherm->drawChar(80, 80, letter[0], RGB(255, 255, 255), RGB(0, color, 0), 4);
		break;
	case 1:
		scherm->drawChar(112, 80, letter[1], RGB(255, 255, 255), RGB(0, color, 0), 4);
		break;
	case 2:
		scherm->drawChar(144, 80, letter[2], RGB(255, 255, 255), RGB(0, color, 0), 4);
	}
}

/*Draws the upper 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
void drawUpper(uint8_t selected, MI0283QT9 *scherm, char *letter) {
	if (letter[selected] == 'A') {
		switch (selected) {
		case 0:
			scherm->drawChar(80, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 1:
			scherm->drawChar(112, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 2:
			scherm->drawChar(144, 40, 'Z', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		}
	}
	else {
		switch (selected) {
		case 0:
			scherm->drawChar(80, 40, (char)(letter[0] - 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 1:
			scherm->drawChar(112, 40, (char)(letter[1] - 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 2:
			scherm->drawChar(144, 40, (char)(letter[2] - 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		}
	}
}

/*Draws the lower 3 letters, gets the int selected because it needs to now what position the character needs to be drawn */
void drawLower(uint8_t selected, MI0283QT9 *scherm, char *letter) {
	if (letter[selected] == 'Z') {
		switch (selected) {
		case 0:
			scherm->drawChar(80, 120, 'A', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 1:
			scherm->drawChar(112, 120, 'A', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 2:
			scherm->drawChar(144, 120, 'A', RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		}
	}
	else {
		switch (selected) {
		case 0:
			scherm->drawChar(80, 120, (char)(letter[0] + 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 1:
			scherm->drawChar(112, 120, (char)(letter[1] + 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		case 2:
			scherm->drawChar(144, 120, (char)(letter[2] + 1), RGB(170, 170, 170), RGB(255, 255, 255), 4);
			break;
		}
	}
}