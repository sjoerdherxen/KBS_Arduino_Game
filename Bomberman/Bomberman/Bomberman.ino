#include "score.h"

//Deze 3 regels kunnen ook weggelaten worden omdat die in de basicdisplay staan als het goed is
void DisplayOn();
void DisplayHighscore();
MI0283QT9 scherm;

int main() {
	init();
	DisplayOn();
	Serial.begin(9600);

	//resetScore();

	_delay_ms(50);

	//TESTCODE
	/* 
	saveScore(22, "MIK");
	saveScore(36, "RIK");
	saveScore(4353, "MAN");
	saveScore(423, "GEK");
	saveScore(6544, "NIK");
	saveScore(1134, "LOL");
	saveScore(9001, "MIK");
	*/

	delay(10);
	printHighscore();
	delay(10);
	DisplayHighscore();
	return 1;
}

//Dit moet bij de BasicDisplay.cpp erin
void DisplayHighscore() {
	//Print "Highscores"
	scherm.drawText(80, 20, "Highscores", RGB(0, 150, 0), RGB(255, 255, 255), 2);

	//Print iedere naam
	char neem[15];
	for (uint8_t i = 0; i < 3; i++) {
		uint8_t b = 0;
		for (uint8_t x = 10 + i * 3; x < i * 3 + 13; x++) {
			neem[b] = getName(x);
			b++;
		}
		scherm.drawText(80, 41 + i * 21, neem, RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
	}

	//Print iedere score
	for (uint8_t i = 0; i < 3; i++) {
		uint8_t a = i * 2;
		scherm.drawInteger(192, 41 + i * 21, getScore(a), 10, RGB(0 + (i * 70), 0 + (i * 70), 0 + (i * 70)), RGB(255, 255, 255), 2);
	}
}

//Dit kan weggelaten worden met het mergen
void DisplayOn() {
	// scherm aanzetten
	scherm.begin();
	scherm.led(40);
	scherm.fillScreen(RGB(255, 255, 255));
}