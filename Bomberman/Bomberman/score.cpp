#include "score.h"

/* function to save score for a specific name */
void saveScore(uint16_t scorePlayer, char name[]) {
	isHighscore(scorePlayer, name);
}

/* function to save the name of a player */
void saveName(uint8_t nameid, char name[]) {
	
	/* switch case to see which ranking the player has */
	switch (nameid) {

	/* for ranking 1 */
	case 1:
		/* save the three letters of the name in the eeprom at the right address */
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 10, name[x]);
		}
		break;

	/* for ranking 2 */
	case 2:
		/* save the three letters of the name in the eeprom at the right address */
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 13, name[x]);
		}
		break;

	/* for ranking 3 */
	case 3:
		/* save the three letters of the name in the eeprom at the right address */
		for (uint8_t x = 0; x < 3; x++) {
			eeprom_write_byte((uint8_t*)x + 16, name[x]);
		}
		break;
	}
}

/* function to get the score of a specific player id */
uint16_t getScore(uint16_t id) {
	uint16_t value = eeprom_read_word((uint16_t*)id);
	eeprom_busy_wait();

	return value;
}

/* function to save a letter */
void saveLetter(uint8_t id, uint16_t letter) {
	eeprom_write_word((uint16_t*)id, letter);
}

/* function to get a name from an id */
uint16_t getName(uint16_t id) {
	uint16_t value = eeprom_read_word((uint16_t*)id);
	eeprom_busy_wait();

	return value;
}

/* function to get a name from an id, to display */
char getNameForDisplay(uint8_t id) {

	char nm[50];

	/* inputs every letter into an array */
	for (uint8_t i = id * 3 + 10; i < id * 3 + 13; i++) {
		uint8_t b = i - 10;
		nm[b] = getName(i);
	}

	return *nm;
}

/* function to down grade the player name in the ranking */
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

/* function used to see which ranking in the highscore a score belongs to */
void isHighscore(uint16_t current, char name[]) {

	/* the current scores are saved in 16-bit integers so the player 
	score can be compared to find the ranking of that score */
	uint16_t score1 = eeprom_read_word((uint16_t*)0);
	uint16_t score2 = eeprom_read_word((uint16_t*)2);
	uint16_t score3 = eeprom_read_word((uint16_t*)4);

	/* if the score higher then the score of the first place */
	if (current > score1) {

		/* the first place score is saved as the second place score,
		the second place score is saved as the third place score and 
		the player score is saved as the first place score */
		eeprom_write_word((uint16_t*)2, score1);
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)0, current);

		/* down grade the names of the first and second place */
		downGradeName(2);
		downGradeName(1);
		saveName(1, name);
	}

	/* if the score is lower then or equal to the first place score */
	else if (current > score2) {

		/* the second place score is saved as the third place score and
		the player score is saved as the second place score */
		eeprom_write_word((uint16_t*)4, score2);
		eeprom_write_word((uint16_t*)2, current);

		/* down grade the name of the second place */
		downGradeName(2);
		saveName(2, name);
	}
	
	/* if the score is lower then or equal to the second place score */
	else if (current > score3) {

		/* the third place score is discarded and the player score
		is saved as the third place score */
		eeprom_write_word((uint16_t*)4, current);

		saveName(3, name);
	}
}

/* function to reset the scores */
void resetScore() {

	/* set all scores to 0 */
	eeprom_write_word((uint16_t*)0, 0);
	eeprom_write_word((uint16_t*)2, 0);
	eeprom_write_word((uint16_t*)4, 0);

	/* set all the saved characters to null */
	for (uint8_t i = 10; i < 19; i++) {
		eeprom_write_word((uint16_t*)i, 0);
	}
}

/* function to print highscores */
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