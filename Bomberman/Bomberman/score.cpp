#include "score.h"

void saveScore(uint16_t scorePlayer, char name[]) {
	isHighscore(scorePlayer, name);
}

void saveName(uint8_t nameid, char name[]) {
	switch (nameid) {
	case 1:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 10, name[x]);
		}
		break;
	case 2:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 13, name[x]);
		}
		break;
	case 3:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 16, name[x]);
		}
		break;
	}
}

void saveLetter(uint8_t id, uint16_t letter) {
	eeprom_write_word((uint16_t*)id, letter);
}

uint16_t getName(uint16_t id) {
	uint16_t value = eeprom_read_word((uint16_t*)id);
	eeprom_busy_wait();

	return value;
}

char getNameForDisplay(uint8_t id) {
	//Zet iedere letter in de array
	char nm[50];
	for (uint8_t i = id * 3 + 10; i < id * 3 + 13; i++) {
		uint8_t b = i - 10;
		nm[b] = getName(i);
	}
	return *nm;
}

void downGradeName(uint8_t id) {
	if (id == 1) {
		for (uint8_t i = 10; i < 12; i++) {
			saveLetter(i + 3, getName(i));
		}
	}
	else if (id == 2) {
		for (uint8_t i = 13; i < 15; i++) {
			saveLetter(i + 3, getName(i));
		}
	}

}

uint16_t getScore(uint16_t id) {
	uint16_t value = eeprom_read_word((uint16_t*)id);
	eeprom_busy_wait();

	return value;
}

void isHighscore(uint16_t current, char name[]) {
	uint16_t score1 = eeprom_read_word((uint16_t*)0);
	uint16_t score2 = eeprom_read_word((uint16_t*)2);
	uint16_t score3 = eeprom_read_word((uint16_t*)4);
	if (current > score1) {
		eeprom_write_word((uint16_t*)2, score1);
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)0, current);
		downGradeName(2);
		downGradeName(1);
		saveName(1, name);
	}
	else if (current > score2) {
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)2, current);
		downGradeName(2);
		saveName(2, name);
	}
	else if (current > score3) {
		eeprom_write_word((uint16_t*)4, current);

		saveName(3, name);
	}
}

void resetScore() {
	eeprom_write_word((uint16_t*)0, 0);
	eeprom_write_word((uint16_t*)2, 0);
	eeprom_write_word((uint16_t*)4, 0);
	for (uint8_t i = 10; i < 19; i++) {
		eeprom_write_word((uint16_t*)i, '-');
	}
}

//If you want to see the current scores on the serial monitor you can execute this
void printHighscore() {
	Serial.println("Highscores:");
	_delay_ms(10);

	for (uint8_t i = 0; i < 3; i++) {
		uint8_t a = i * 2;
		uint8_t b = i + 1;
		uint8_t c = i * 3 + 10;
		Serial.print(b);
		_delay_ms(10);
		Serial.print(": ");
		_delay_ms(10);
		Serial.print(getScore(a));
		_delay_ms(10);
		Serial.print(" - ");
		_delay_ms(10);
		for (uint8_t x = c; x < c + 3; x++) {
			Serial.write(getName(x));
			_delay_ms(10);
		}
		Serial.print("\n");
		_delay_ms(10);
	}
}

