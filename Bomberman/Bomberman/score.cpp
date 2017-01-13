#include "score.h"

/* function to save the score for a specific name */
void saveScore(uint16_t scorePlayer, char name[]) {
	isHighscore(scorePlayer, name);
}

/* function to save the name of a player */
void saveName(uint8_t nameid, char name[]) {

	switch (nameid) {

	/* for the first letter */
	case 1:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 10, name[x]);
		}
		break;

	/* for the second letter */
	case 2:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 13, name[x]);
		}
		break;

	/* for the third letter */
	case 3:
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 16, name[x]);
		}
		break;
	}
}

/* function to save a letter */
void saveLetter(uint8_t id, uint16_t letter) {

	/* write a letter (one word) to the eeprom */
	eeprom_write_word((uint16_t*)id, letter);
}

/* function to get the name for a specific id */
uint16_t getName(uint16_t id) {

	/* read the name from the eeprom */
	uint16_t value = eeprom_read_word((uint16_t*)id);

	/* wait until the eeprom is done reading */
	eeprom_busy_wait();

	return value;
}

/* function to get the name for a specific id, used to display */
char getNameForDisplay(uint8_t id) {

	/* put every letter in an array */
	char nm[50];

	/* for loop looping through the letters of the name */
	for (uint8_t i = id * 3 + 10; i < id * 3 + 13; i++) {
		uint8_t b = i - 10;
		nm[b] = getName(i);
	}

	return *nm;
}

/* function used to down grade the name */
void downGradeName(uint8_t id) {

	/* if the id is equal to 1 */
	if (id == 1) {
		for (uint8_t i = 10; i < 12; i++) {
			saveLetter(i + 3, getName(i));
		}
	}

	/* if the id is equal to 2 */
	else if (id == 2) {
		for (uint8_t i = 13; i < 15; i++) {
			saveLetter(i + 3, getName(i));
		}
	}

}

/* function used to get the score for a specific id */
uint16_t getScore(uint16_t id) {

	/* read the score from the eeprom */
	uint16_t value = eeprom_read_word((uint16_t*)id);

	/* wait until the eeprom is done reading */
	eeprom_busy_wait();

	return value;
}

/* function used to check if the achieved score fits into the highscore */
void isHighscore(uint16_t current, char name[]) {

	/* import the three top scores form the highscore */
	uint16_t score1 = eeprom_read_word((uint16_t*)0);
	uint16_t score2 = eeprom_read_word((uint16_t*)2);
	uint16_t score3 = eeprom_read_word((uint16_t*)4);

	/* if the achieved score is higher then the first place score, downgrade all the scores and
	set the achieved score as the first place score */
	if (current > score1) {
		eeprom_write_word((uint16_t*)2, score1);
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)0, current);
		downGradeName(2);
		downGradeName(1);
		saveName(1, name);
	}

	/* if the achieved score is higher then the second place score but lower then the first place score,
	downgrade the second and third place scores and set the achieved score as the first place score */
	else if (current > score2) {
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)2, current);
		downGradeName(2);
		saveName(2, name);
	}

	/* if the achieved score is higher then the third place score but lower then the second place score,
	set the achieved score as the thrid place score and delete the last third place score */
	else if (current > score3) {
		eeprom_write_word((uint16_t*)4, current);

		saveName(3, name);
	}
}

/* function to reset all scores */
void resetScore() {
	eeprom_write_word((uint16_t*)0, 0);
	eeprom_write_word((uint16_t*)2, 0);
	eeprom_write_word((uint16_t*)4, 0);
	for (uint8_t i = 10; i < 19; i++) {
		eeprom_write_word((uint16_t*)i, '-');
	}
}
