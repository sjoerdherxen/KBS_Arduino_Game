#include "Keyboard.h"

char* showMiddle(MI0283QT9 *scherm) {
	Serial.begin(9600);
	Serial.println("Test");
	uint8_t selectedLetter = 0;
	Serial.println("Test2");
	uint8_t value = Nunchuck_get_data();
	Serial.println("Test3");
	char letter[3];

	for (int i = 0; i < 3; i++) {
		letter[i] = 'A';
	}

	while (1) {
		Serial.println("Begin");
		delay(150);
		value = Nunchuck_get_data();

		if (value == 2) {
			Serial.println("Begin1");
			if (selectedLetter < 3) {
				Serial.println("Begin2");
				drawLetter(selectedLetter, scherm, letter, WHITE);
				selectedLetter++;
				drawLetter(selectedLetter, scherm, letter, GREEN);
			}
		}
		else if (value == 4) {
			if (selectedLetter > 0) {
				drawLetter(selectedLetter, scherm, letter, WHITE);
				selectedLetter--;
				drawLetter(selectedLetter, scherm, letter, GREEN);
			}
		}

		if (selectedLetter <= 2) {
			if (value == 3) {
				letter[selectedLetter]++;
				if (letter[selectedLetter] > 'Z') {
					letter[selectedLetter] = 'A';
				}
				drawUpper(selectedLetter, scherm, letter);
				drawLetter(selectedLetter, scherm, letter, GREEN);
				drawLower(selectedLetter, scherm, letter);
			}
			else if (value == 1) {
				letter[selectedLetter]--;
				if (letter[selectedLetter] < 'A') {
					letter[selectedLetter] = 'Z';
				}
				drawUpper(selectedLetter, scherm, letter);
				drawLetter(selectedLetter, scherm, letter, GREEN);
				drawLower(selectedLetter, scherm, letter);
			}
		}
		else {
			scherm->drawText(184, 90, "Confirm", RGB(255, 255, 255), RGB(0, 0, 0), 2);
			if (value & 0x40) {
				showMainMenu();
				return letter;
			}
		}


		if (selectedLetter < 3) {
			scherm->drawText(184, 90, "Confirm", RGB(0, 0, 0), RGB(255, 255, 255), 2);
		}
		Serial.println("Geprint");
	}
}

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