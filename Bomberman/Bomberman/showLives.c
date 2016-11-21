#include "showLives.h"

void setPorts();
void resetLives();
void startLives();
int loseLife(int lives);

int lives = 0;
int check = 0;

void setPorts() {
	DDRD |= (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
	DDRB |= (1 << PORTB0) | (1 << PORTB1);
}

void startLives() {
	PORTD |= (1 << 5);
	PORTD |= (1 << 6);
	PORTD |= (1 << 7);
	PORTB |= (1 << 0);
	PORTB |= (1 << 1);

	lives = 5;
}

int loseLife(int lives) {
	lives--;
	check = lives;
	switch (check) {
	case 4:
		PORTD &= ~(1 << 5);
		break;
	case 3:
		PORTD &= ~(1 << 6);
		break;
	case 2:
		PORTD &= ~(1 << 7);
		break;
	case 1:
		PORTB &= ~(1 << 0);
		break;
	case 0:
		PORTB &= ~(1 << 1);
		break;
	}

	return lives;
}

int main() {
	init();
	setPorts();

	Serial.begin(9600);

	while (1) {
		startLives();	

		Serial.print("HOI");
		
		delay(1000);
		loseLife(lives);	
		delay(2000);
		loseLife(lives);			
		delay(2000);
		loseLife(lives);		
		delay(2000);
		loseLife(lives);
		delay(2000);
		loseLife(lives);

		if (lives == 0) {
			//dieHard();
		}

		/*

		delay(50);
		PORTD &= ~(1 << 5);
		delay(50);
		PORTD &= ~(1 << 6);
		delay(50);
		PORTD &= ~(1 << 7);
		delay(50);
		PORTB &= ~(1 << 0);
		delay(50);
		PORTB &= ~(1 << 1);
		delay(50);
		*/
	}
	return 0;
}