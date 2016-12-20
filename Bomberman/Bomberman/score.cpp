#include <Arduino.h>
#include "score.h"
#include "eeprom.h"

void saveScore(uint16_t scorePlayer, uint16_t id) {

	_delay_ms(10);

	isHighscore(scorePlayer);
}

uint16_t getScore(uint16_t id) {
	uint16_t value = eeprom_read_word((uint16_t*)id);
	eeprom_busy_wait();

	return value;
}

void isHighscore(uint16_t current) {
	uint16_t score1 = eeprom_read_word((uint16_t*)0);
	uint16_t score2 = eeprom_read_word((uint16_t*)2);
	uint16_t score3 = eeprom_read_word((uint16_t*)4);

	if (current > score1) {
		eeprom_write_word((uint16_t*)2, score1);
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)0, current);
	}
	else if (current > score2) {
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)0, current);
	}
	else if (current > score3) {
		eeprom_write_word((uint16_t*)4, current);
	}
}

void resetScore() {
	eeprom_write_word((uint16_t*)0, 0);
	eeprom_write_word((uint16_t*)2, 0);
	eeprom_write_word((uint16_t*)4, 0);
}

void printHighscore() {
	Serial.println("Highscores:");
	_delay_ms(10);

	for (int i = 0; i < 3; i++) {
		int a = i * 2;
		int b = i + 1;
		Serial.print(b);
		_delay_ms(10);
		Serial.print(": ");
		_delay_ms(10);
		Serial.println(getScore(a));
		_delay_ms(10);
	}
}