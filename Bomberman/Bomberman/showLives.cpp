#include "showLives.h"									//All functions are declared in the showLives.h headerfile

int lives = 0;											//Initializes and declares lives to 0

const uint8_t patterns[] PROGMEM = {
	0b11100000,
	0b11110000,
	0b11111000,
	0b11111100,
	0b11111110,
	0b11111111,

	0b11111011,
	0b11110001,
	0b11100100,
	0b11101110,
};

void setupExpander() {
	Wire.begin();
}

void startLives() {										//Turns all leds on which is equal to having 5 lives
	Wire.beginTransmission(56);
	Wire.write(pgm_read_byte(&patterns[0]));			
	Wire.endTransmission();
	lives = 5;											//Sets lives to 5		
}

void blink(int check2) {								//Makes the leds blink when a live is lost
	for (int i = 0; i < 3; i++) {
		switch (check2) {								//Checks how many lives the player has and which leds have to be animated
		case 4:											//What the leds should look like: (o = on and x = off)
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[0]));
			Wire.endTransmission();						//ooooo
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 3:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[1]));
			Wire.endTransmission();						//oooox					
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 2:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[2]));
			Wire.endTransmission();						//oooxx
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 1:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[3]));
			Wire.endTransmission();						//ooxxx
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		}
	}
}

void loseLife() {										//Activates the blinking and after that the amount of leds equal to the amount of lives is set.
	lives--;											//Sets lives to one less, for instance: from 4 to 3
	switch (lives) {									//Checks how many lives the player has and which leds have to be displayed
	case 4:												//What the leds should look like: (o = on and x = off)
		blink(lives);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[1]));
		Wire.endTransmission();							//oooox
		break;
	case 3:
		blink(lives);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[2]));
		Wire.endTransmission();							//oooxx
		break;
	case 2:
		blink(lives);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[3]));
		Wire.endTransmission();							//ooxxx
		break;
	case 1:
		blink(lives);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[4]));
		Wire.endTransmission();							//oxxxx
		break;
	case 0:
		blink(lives);
		endOfGame();									//xxxxxx
		break;
	}
}

void endOfGame() {										//Makes the leds animate when there are no more lives and keeps the leds off
	for (int i = 0; i < 2; i++) {						//What the leds should look like: (o = on and x = off)
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[6]));
		Wire.endTransmission();							//xxoxx
		_delay_ms(200);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[7]));
		Wire.endTransmission();							//xooox
		_delay_ms(200);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[8]));
		Wire.endTransmission();							//ooxoo
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[9]));
		Wire.endTransmission();							//oxxxo
		_delay_ms(200);
		Wire.beginTransmission(56);
		Wire.write(pgm_read_byte(&patterns[5]));
		Wire.endTransmission();							//xxxxx
		_delay_ms(200);
	}
}