#include "showLives.h"											//All functions are declared in the showLives.h headerfile

int check = 0;

void setupPorts() {												//Sets all the ports that are needed to an output
	DDRD |= (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
	DDRB |= (1 << PORTB0) | (1 << PORTB1);
}

void startLives(int *lives) {									//Turns all leds on which is equal to having 5 lives
	PORTD |= (1 << 5) | (1 << 6) | (1 << 7);
	PORTB |= (1 << 0) | (1 << 1);

	*lives = 5;
}

void blink(int check2) {										//Makes the leds blink when a live is lost
	for (int i = 0; i < 3; i++) {
		switch (check2) {
		case 4:
			PORTD |= (1 << 5) | (1 << 6) | (1 << 7);
			PORTB |= (1 << 0) | (1 << 1);
			_delay_ms(200);
			PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);
			_delay_ms(200);
			break;
		case 3:
			PORTD |= (1 << 6) | (1 << 7);
			PORTB |= (1 << 0) | (1 << 1);
			_delay_ms(200);
			PORTD &= ~(1 << 6) & ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);
			_delay_ms(200);
			break;
		case 2:
			PORTD |= (1 << 7);
			PORTB |= (1 << 0) | (1 << 1);
			_delay_ms(200);
			PORTD &= ~(1 << 7);
			PORTB &= ~(1 << 0) & ~(1 << 1);
			_delay_ms(200);
			break;
		case 1:
			PORTB |= (1 << 0) | (1 << 1);
			_delay_ms(200);
			PORTB &= ~(1 << 0) & ~(1 << 1);
			_delay_ms(200);
			break;
		}
	}
}

void loseLife(int *lifeCount) {									//Activates the blinking and after that the amount of leds equal to the amount of lives is set.
	check = *lifeCount;
	check--;
	*lifeCount = check;											//Takes away one life

	switch (check) {
	case 4:
		blink(check);
		PORTD |= (1 << 6) | (1 << 7);
		PORTB |= (1 << 0) | (1 << 1);
		break;
	case 3:
		blink(check);
		PORTD |= (1 << 7);
		PORTB |= (1 << 0) | (1 << 1);
		break;
	case 2:
		blink(check);
		PORTB |= (1 << 0) | (1 << 1);
		break;
	case 1:
		blink(check);
		PORTB |= (1 << 1);
		break;
	case 0:
		blink(check);
		PORTB &= ~(1 << 1);
		endOfGame();
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
		PORTB &= ~(1 << 0) & ~(1 << 1);
		break;
	}
}

void endOfGame() {												//Makes the leds animate when there are no more lives and keeps the leds off
	for (int i = 0; i < 2; i++) {
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
		PORTB &= ~(1 << 0) & ~~(1 << 1);

		PORTD |= (1 << 7);
		_delay_ms(100);
		PORTD |= (1 << 6) | (1 << 7);
		PORTB |= (1 << 0);
		_delay_ms(100);
		PORTD |= (1 << 5) | (1 << 6);
		PORTD &= ~(1 << 7);
		PORTB |= (1 << 0) | (1 << 1);
		_delay_ms(100);
		PORTD |= (1 << 5); 
		PORTD &= ~(1 << 6);
		PORTB &= ~(1 << 0); 
		PORTB |= (1 << 1);
		_delay_ms(100);
		PORTD &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
		PORTB &= ~(1 << 0) & ~(1 << 1);
		_delay_ms(100);
	}
}