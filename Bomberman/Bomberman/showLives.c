void setupLives();
void resetLives();
int loseLife(int lives);
void dieHard();
void endGame();

int lives;

void main() {
	init();
	setupLives();

	if (lives == 0) {
		dieHard();
	}
}

void setupLives() {
	DDRD |= (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
	DDRB |= (1 << PORTB0) | (1 << PORTB1);

	lives = 5;
}

void resetLives() {
	PORTD = (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
	PORTB = (1 << PORTB0) | (1 << PORTB1);

	lives = 5;
}

int loseLife(int lives) {
	lives--;

	return lives;
}

void dieHard() {
	endGame();
}