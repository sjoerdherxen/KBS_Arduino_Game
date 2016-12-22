#include "score.h"

int main() {
	init();
	Serial.begin(9600);

	resetScore();

	_delay_ms(50);

	//TESTCODE
	saveScore(22, "AAA");
	saveScore(11, "BBB");
	saveScore(5, "CCC");
	saveScore(6, "DDD");
	saveScore(12, "EEE");
	saveScore(123, "FFF");

	/*
	_delay_ms(100);
	saveScore(9001, "GGG");	// 1
	_delay_ms(100);
	saveScore(59302, "HHH");// 1
	_delay_ms(100);
	saveScore(474, "III");	// 3
	_delay_ms(100);
	*/

	delay(10);
	printHighscore();
	delay(10);
	//DisplayHighscore();
	return 1;
}

