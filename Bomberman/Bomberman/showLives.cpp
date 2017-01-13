#include "showLives.h"									

/* initializes and declares lives to 0 */
extern uint8_t player1Lives;
extern uint8_t player2Lives;

/* declares the end of the game */
uint8_t ifEndGame = 0;

/* value to store the gametick */
uint16_t endOfGameTick = 0;

/* patterns for the which leds have to be on at certain times, the first 3 bits are not used */
const uint8_t patterns[] PROGMEM = {

	/* 6 patterns for showing lives */
	0b11111111,
	0b11111110,
	0b11111100,
	0b11111000,
	0b11110000,
	0b11100000,

	/* 4 patters for the end-game animation */
	0b11111011,
	0b11110001,
	0b11100100,
	0b11101110,
};

/* function used to setup the port expander */
void setupExpander() {
	Wire.begin();
}

/* function to turn on all leds, equal to a player having 5 full lives */
void startLives() {

	/* begin transmission on address 56 */
	Wire.beginTransmission(56);

	/* writes the pattern that corresponds to the 0 to the address */
	Wire.write(pgm_read_byte(&patterns[5]));

	/* ends all transmission */
	Wire.endTransmission();

	/* sets the value of lives to 5 */
	player1Lives = 5;
}

/* activates the blinking and after that the amount of leds equal to the amount of lives is set */
void loseLife(uint16_t count) {

	/* checks how many lives the player has and which leds have to be displayed */
	if (player1Lives && player2Lives) {

		/* begins transmission on address 56 */
		Wire.beginTransmission(56);

		/* writes the pattern that corresponds to lives to the adress */
		Wire.write(pgm_read_byte(&patterns[player1Lives]));

		/* ends all transmissions */
		Wire.endTransmission();
	}
	else {

		/* the endOfGameTick integer gets the current gametick value */
		endOfGameTick = count;

		/* starts the gameOver animation and gives the current gametick value with it */
		startGameOver(count);

		/* ifEndGame gets the value 3, it is set to 3 so the animation will be executed 3 times */
		ifEndGame = 3;
	}
}

/* this is the animation the game will execute when a player is dead */
void endOfGame(uint16_t count) {
	/* if ifEnGame is >=1 this part of the code will be executed, every time this code is executed */ 
	/* ifEndGame gets - 1 so at some point it will reach 0 and this part of the code won't be executed anymore */
	if (ifEndGame) {
		if (count == endOfGameTick) {
			/* begins transmission to adress 56 */
			Wire.beginTransmission(56);

			/* writes the pattern that corresponds to xxoxx */
			Wire.write(pgm_read_byte(&patterns[6]));

			/* ends all transmissions */
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 2) {
			/* begins transmission to adress 56 */
			Wire.beginTransmission(56);

			/* writes the pattern that corresponds to xooox */
			Wire.write(pgm_read_byte(&patterns[7]));

			/* ends all transmissions */
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 4) {
			/* begins transmission to adress 56 */
			Wire.beginTransmission(56);

			/* writes the pattern that corresponds to ooxoo */
			Wire.write(pgm_read_byte(&patterns[8]));

			/* ends all transmissions */
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 6) {
			/* begins transmission to adress 56 */
			Wire.beginTransmission(56);

			/* writes the pattern that corresponds to oxxxo */
			Wire.write(pgm_read_byte(&patterns[9]));

			/* ends all transmissions */
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 8) {

			/* begins transmission to adress 56 */
			Wire.beginTransmission(56);

			/* writes the pattern that corresponds to xxxxx */
			Wire.write(pgm_read_byte(&patterns[0]));

			/* ends all transmissions */
			Wire.endTransmission();

			ifEndGame--;
			endOfGameTick = count;
		}

		if (ifEndGame == 0) {

			/* this will start the GameOverMenu */
			setGameover(1);
			uint8_t selectie = gameOverMenu();

			if (selectie == 1) {
				/* rebooting the arduino to go to the main menu and clear the memory */
				__asm volatile ("  jmp 0");
			}
			else if (selectie == 2) {
				DisplayKeyboard();
			}

		}
	}
}