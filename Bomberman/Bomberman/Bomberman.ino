#include <Arduino.h>
#include "score.h"

int main() {
	init();
	Serial.begin(9600);

	resetScore();

	_delay_ms(50);

	/*saveScore(596, 0);
	saveScore(7566, 2);
	saveScore(11, 4);
	saveScore(11432, 6);
	saveScore(65535, 8);
	saveScore(0, 8);

	printHighscore();*/

	char text = 'h';

	eeprom_write_byte((uint8_t*)1, (uint8_t)text);

	delay(10);

	Serial.println(eeprom_read_byte((uint8_t*)1));
	delay(10);

	return 1;
}
