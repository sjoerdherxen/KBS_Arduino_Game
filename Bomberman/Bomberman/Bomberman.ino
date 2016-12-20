#include <Arduino.h>
#include "score.h"

int main() {
	init();
	Serial.begin(9600);

	resetScore();
	_delay_ms(50);

	//saveScore(322, 0);


	
	Serial.println(getScore(0));
	_delay_ms(10);

	Serial.println(getScore(2));
	_delay_ms(10);

	Serial.println(getScore(4));
	_delay_ms(10);

	return 1;
}
