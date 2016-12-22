#include "Keyboard.h"

char* showMiddle() {
	uint8_t selectedLetter = 0;
	uint8_t value = Nunchuck_get_data();
	char letter[3];

	for (int i = 0; i < 3; i++) {
		letter[i] = 'A';
	}

	while (1) {
		delay(100);
		if (value == 2) {
			if (selectedLetter < 3) {
				selectedLetter++;
			}
		}
		else if (value == 4) {
			if (selectedLetter > 0) {
				selectedLetter--;
			}
		}

		if (selectedLetter <= 2) {
			if (value == 1) {
				letter[selectedLetter]++;
				if (letter[selectedLetter] > 'Z') {
					letter[selectedLetter] = 'A';
				}
			}
			else if (value == 3) {
				letter[selectedLetter]--;
				if (letter[selectedLetter] > 'A') {
					letter[selectedLetter] = 'Z';
				}
			}
		}
		else {
			if (value & 0x40) {
				return letter;
			}
		}
		scherm.drawChar(80, 80, letter[0], RGB(255, 255, 255), RGB(0, 0, 0), 4);
		scherm.drawChar(112, 80, letter[1], RGB(255, 255, 255), RGB(0, 0, 0), 4);
		scherm.drawChar(144, 80, letter[2], RGB(255, 255, 255), RGB(0, 0, 0), 4);
	}
}
