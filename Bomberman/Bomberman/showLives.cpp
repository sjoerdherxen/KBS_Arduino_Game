#include "showLives.h"											//All functions are declared in the showLives.h headerfile

int lives;

void setupPorts() {												//Sets all the ports that are needed to an output
	//DDRD |= (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);		//Digital ports 5, 6 & 7
	//DDRB |= (1 << PORTB0) | (1 << PORTB1);						//And digital ports 8 & 9 set to output
}

void startLives() {									//Turns all leds on which is equal to having 5 lives
	//PORTD |= (1 << 5) | (1 << 6) | (1 << 7);					//Digital ports 5, 6 & 7
	//PORTB |= (1 << 0) | (1 << 1);								//And digital ports 8 & 9 output power

	lives = 5;													//Needs to be a pointer because otherwise it won't be able to change the value of lives
}

void blink(int check2) {	
	/*Makes the leds blink when a live is lost
	for (int i = 0; i < 3; i++) {
		switch (check2) {										//Checks how many lives the player has and which leds have to be animated
		case 4:													//What the leds should look like: (o = on and x = off)
			PORTD |= (1 << 5) | (1 << 6) | (1 << 7);			
			PORTB |= (1 << 0) | (1 << 1);						//ooooo
			_delay_ms(200);
			PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);						//xxxxx
			_delay_ms(200);
			break;
		case 3:
			PORTD |= (1 << 6) | (1 << 7);	
			PORTB |= (1 << 0) | (1 << 1);						//oooox					
			_delay_ms(200);
			PORTD &= ~(1 << 6) & ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);						//xxxxx
			_delay_ms(200);
			break;
		case 2:
			PORTD |= (1 << 7);
			PORTB |= (1 << 0) | (1 << 1);						//oooxx
			_delay_ms(200);
			PORTD &= ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);						//xxxxx
			_delay_ms(200);
			break;
		case 1:
			PORTB |= (1 << 0) | (1 << 1);						//ooxxx
			_delay_ms(200);
			PORTB &= ~(1 << 0) & ~(1 << 1);						//xxxxx
			_delay_ms(200);
			break;
		}
	}*/
}

void loseLife() {										//Activates the blinking and after that the amount of leds equal to the amount of lives is set.
	lives--;												//Sets lives to one less, for instance: from 4 to 3
	/*
	switch (lives) {											//Checks how many lives the player has and which leds have to be displayed
	case 4:														//What the leds should look like: (o = on and x = off)
		blink(lives);
		PORTD |= (1 << 6) | (1 << 7);
		PORTB |= (1 << 0) | (1 << 1);							//oooox
		break;
	case 3:
		blink(lives);
		PORTD |= (1 << 7);
		PORTB |= (1 << 0) | (1 << 1);							//oooxx
		break;
	case 2:
		blink(lives);
		PORTB |= (1 << 0) | (1 << 1);							//ooxxx
		break;
	case 1:
		blink(lives);
		PORTB |= (1 << 1);										//oxxxx
		break;
	case 0:
		blink(lives);
		PORTB &= ~(1 << 1);
		endOfGame();
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
		PORTB &= ~(1 << 0) & ~(1 << 1);							//xxxxxx
		break;
	}
	*/
}

void endOfGame() {			
	/*//Makes the leds animate when there are no more lives and keeps the leds off
	for (int i = 0; i < 2; i++) {								//What the leds should look like: (o = on and x = off)
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);				
		PORTB &= ~(1 << 0) & ~(1 << 1);							//xxxxx

		PORTD |= (1 << 7);										//xxoxx
		_delay_ms(100);
		PORTD |= (1 << 6);
		PORTB |= (1 << 0);										//xooox
		_delay_ms(100);
		PORTD |= (1 << 5);
		PORTD &= ~(1 << 7);
		PORTB |= (1 << 1);										//ooxoo
		_delay_ms(100);
		PORTD &= ~(1 << 6);
		PORTB &= ~(1 << 0); 									//oxxxo
		_delay_ms(100);
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
		PORTB &= ~(1 << 0) & ~(1 << 1);							//xxxxx
		_delay_ms(100);
	}*/
}