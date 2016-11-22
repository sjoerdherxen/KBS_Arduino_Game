#include <Arduino.h>
#include "soundEffects.h"

unsigned long time = 0;;

void setupSpeaker() {

	/* setting pin 4 as output for the speaker */
	DDRD |= (1 << PORTD4);
}

// ** Start **

void playStart() {
	/* this only plays the games music for now, maybe more imput later */
	playMusic();
}

// ** Explosion **

void playExplosion() {

	/* a loop of 2000 ms (the time that the explosion is heard) this can be
	changed by changing the value to a different one */
	while (time <= 2000) {
		time++;

		/* the tone() function creates a tone on the given pin. the frequenty of the
		tone is created using the random() function, which creates a random number 
		between the given values, so the tone can be changed by changing these values */
		tone(4, random(100, 1000));
	}

	/* the noTone() function stops the tone being outputted */
	noTone(4);

	time = 0;
}

// ** Lose Life **

/* notes to be used in playLoseLife() */
int loseLife[] = {
	NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3,
};

/* tempo of the notes */
int loseLifeTempo[] = {
	12, 12, 12, 12,
};

/* playing the sound */
void playLoseLife() {

	/* size is used in the for loop to show the length of the song */
	int size = sizeof(loseLife) / sizeof(int);

	/* a for loop that plays the notes in the right order */
	for (int note = 0; note < size; note++) {

		/* for the duration of the note, the tempo from musicTempo[] has to be devided
		by 1000 ms, a full note would be 1000 / 1, a half a note would be 1000 / 2 and
		a quarter of a note would be 1000 / 4 etc... */
		int noteDuration = 1000 / loseLifeTempo[note];

		/* here the note is actually being played using the tone() function */
		tone(4, loseLife[note], noteDuration);

		/* if you don't want the sound to become absolute rubbish, a delay should be
		put in, a delay of 140 seems to work well */
		_delay_ms(100);

		/* the noTone() function stops the tones being outputted */
		noTone(4);
	}
}

// ** Game Over **

/* notes to be used in playGameOver() */
int gameOver[] = {
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_E3,
	NOTE_D3, NOTE_C3, NOTE_D3, NOTE_C3,
	NOTE_B2, NOTE_A2, NOTE_F2, NOTE_D2,
};

/* tempo of the notes */
int gameOverTempo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

/* playing the sound */
void playGameOver() {

	/* size is used in the for loop to show the length of the song */
	int size = sizeof(gameOver) / sizeof(int);

	/* a for loop that plays the notes in the right order */
	for (int note = 0; note < size; note++) {

		/* for the duration of the note, the tempo from musicTempo[] has to be devided
		by 1000 ms, a full note would be 1000 / 1, a half a note would be 1000 / 2 and
		a quarter of a note would be 1000 / 4 etc... */
		int noteDuration = 1000 / gameOverTempo[note];

		/* here the note is actually being played using the tone() function */
		tone(4, gameOver[note], noteDuration);

		/* if you don't want the sound to become absolute rubbish, a delay should be
		put in, a delay of 140 seems to work well */
		_delay_ms(150);

		/* the noTone() function stops the tones being outputted */
		noTone(4);
	}
}

// ** Music **

/* notes to be used in playMusic() */
int music[] = {
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,

	NOTE_F2, NOTE_E2, NOTE_D2, NOTE_C2,
	NOTE_B2, NOTE_A2, NOTE_G1, NOTE_F1,
	NOTE_F2, NOTE_E2, NOTE_D2, NOTE_C2,
	NOTE_B2, NOTE_A2, NOTE_G1, NOTE_F1,

	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,

	NOTE_F2, NOTE_E2, NOTE_D2, NOTE_C2,
	NOTE_B2, NOTE_A2, NOTE_G1, NOTE_F1,
	NOTE_F2, NOTE_E2, NOTE_D2, NOTE_C2,
	NOTE_B2, NOTE_A2, NOTE_G1, NOTE_F1,

	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,
	
	NOTE_F3, // BREAK

	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B4, NOTE_A3, NOTE_G3, NOTE_F3,
	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B4, NOTE_A3, NOTE_G3, NOTE_F3,

	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G3, NOTE_F3,
	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G3, NOTE_F3,

	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B4, NOTE_A3, NOTE_G3, NOTE_F3,
	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B4, NOTE_A3, NOTE_G3, NOTE_F3,

	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G3, NOTE_F3,
	NOTE_F4, NOTE_E3, NOTE_D4, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G3, NOTE_F3,

	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_C3,
	NOTE_B3, NOTE_A3, NOTE_G2, NOTE_F2,

	0,
};

/* tempo of the notes */
int musicTempo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	4, // BREAK

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	8,
};

/* playing the sound */
void playMusic() {

	/* size is used in the for loop to show the length of the song */
	int size = sizeof(music) / sizeof(int);

	/* a for loop that plays the notes in the right order */
	for (int note = 0; note < size; note++) {

		/* for the duration of the note, the tempo from musicTempo[] has to be devided 
		by 1000 ms, a full note would be 1000 / 1, a half a note would be 1000 / 2 and 
		a quarter of a note would be 1000 / 4 etc... */
		int noteDuration = 1000 / musicTempo[note];

		/* here the note is actually being played using the tone() function */
		tone(4, music[note], noteDuration);

		/* if you don't want the sound to become absolute rubbish, a delay should be
		put in, a delay of 100 seems to work well */
		_delay_ms(100);

		/* the noTone() function stops the tones being outputted */
		noTone(4);
	}
}