#include <Arduino.h>
#include "score.h"
#include "eeprom.h"

void saveScore(uint16_t scorePlayer, uint16_t id) {
	isHighscore(scorePlayer);
}

uint16_t getScore(uint16_t id) {
	uint16_t value = eeprom_read_word(&id);
	eeprom_busy_wait();

	return value;
}

int isHighscore(uint16_t scorePlayer) {
	uint16_t score1 = eeprom_read_word((uint16_t*)0);
	uint16_t score2 = eeprom_read_word((uint16_t*)2);
	uint16_t score3 = eeprom_read_word((uint16_t*)4);
	
	if (scorePlayer > score1) {
		eeprom_write_word((uint16_t*)0, scorePlayer);
		return 1;
	}
	else if (scorePlayer > score2) {
		eeprom_write_word((uint16_t*)2, scorePlayer);
		return 1;
	}
	else if (scorePlayer > score3) {
		eeprom_write_word((uint16_t*)4, scorePlayer);
		return 1;
	}
	else {
		return 0;
	}
}

void resetScore() {
	eeprom_write_word((uint16_t*)0, 0);
	eeprom_busy_wait();
	eeprom_write_word((uint16_t*)2, 0);
	eeprom_busy_wait();
	eeprom_write_word((uint16_t*)4, 0);
	eeprom_busy_wait();
}
