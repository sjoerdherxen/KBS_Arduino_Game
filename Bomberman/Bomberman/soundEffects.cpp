#include <Arduino.h>
#include "soundEffects.h"

//unsigned long time = 0;

/* integers for the explosion sound */
uint8_t ifPlayExplosion = 0;
uint16_t playExplosionTick = 0;

/* integers for the lose life sound */
uint8_t ifPlayLoseLife = 0;
uint16_t playLoseLifeTick = 0;

/* integers for the game over sound */
uint8_t ifPlayGameOver = 0;
uint16_t playGameOverTick = 0;

/* integers for the music */
uint8_t ifPlayMusic = 0;
uint16_t playMusicTick = 0;

void setupSpeaker() {
	/* setting pin 4 as output for the speaker */
	DDRC |= (1 << PORTC1);
}

// ** Explosion **

/* function to start the explosion sound */
void startExplosion(uint16_t count) {
	ifPlayExplosion = 1;
	playExplosionTick = count;
}

/* function that contains the tones of the explosion */
void playExplosion(uint16_t count) {

	/* the ifPlayExplosion variable is initialized in the function above */
	if (ifPlayExplosion) {

		/* counting the gameticks */
		uint8_t t = (count - playExplosionTick);

		/* if the gametick hits the 10, stop the explosion sound */
		if (t = 10) {

			/* stop playing sound on the speaker */
			noTone(15);
			/* set the ifPlayExplosion variable to 0, to stop the explosion function */
			ifPlayExplosion = 0;
			return;
		}

		/* stop playing sound on the speaker */
		noTone(15);

		/* play sound on the speaker with random frequencies between 100 and 1000 */
		tone(15, random(100, 1000));
	}

	///* a loop of 2000 ms (the time that the explosion is heard) this can be
	//changed by changing the value to a different one */
	//while (time <= 2000) {
	//	time++;

	//	/* the tone() function creates a tone on the given pin. the frequenty of the
	//	tone is created using the random() function, which creates a random number
	//	between the given values, so the tone can be changed by changing these values */
	//	tone(4, random(100, 1000));
	//}

	///* the noTone() function stops the tone being outputted */
	//noTone(4);

	//time = 0;
}

// ** Lose Life **

/* notes to be used in playLoseLife(), initialized in soundEffects.h */
uint16_t loseLife[] = {
	NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3,
};

///* tempo of the notes */
//int loseLifeTempo[] = {
//	12, 12, 12, 12,
//};

/* function to start the lose life sound */
void startLoseLife(uint16_t count) {
	ifPlayLoseLife = 1;
	playLoseLifeTick = count;
}

/* function that contains the tones of the lose life sound */
void playLoseLife(uint16_t count) {

	/* the ifPlayLoseLife variable is initialized in the function above */
	if (ifPlayLoseLife) {

		/* at the first game tick, play the first note of the lose life sound */
		if (count == playLoseLifeTick) {
			tone(15, loseLife[0], 83);
		}

		/* at the second game tick, play the second note of the lose life sound */
		else if (count == playLoseLifeTick + 1) {
			noTone(15);
			tone(15, loseLife[1], 83);
		}

		/* at the third game tick, play the third note of the lose life sound */
		else if (count == playLoseLifeTick + 2) {
			noTone(15);
			tone(15, loseLife[2], 83);
		}

		/* at the fourth game tick, play the fourth note of the lose life sound */
		else if (count == playLoseLifeTick + 3) {
			noTone(15);
			tone(15, loseLife[3], 83);
		}

		/* at the fifth game tick, play the fifth note of the lose life sound */
		else if (count == playLoseLifeTick + 4) {
			noTone(15);
			ifPlayLoseLife = 0;
		}
	}
}

// ** Game Over **

/* notes to be used in playGameOver() */
int gameOver[] = {
	NOTE_F3, NOTE_E3, NOTE_D3, NOTE_E3,
	NOTE_D3, NOTE_C3, NOTE_D3, NOTE_C3,
	NOTE_B2, NOTE_A2, NOTE_F2, NOTE_D2,
};

///* tempo of the notes */
//int gameOverTempo[] = {
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//};

/* function to start the game over sound */
void startGameOver(uint16_t count) {
	ifPlayGameOver = 1;
	playGameOverTick = count;
}

/* function that contains the tones of the game over sound */
void playGameOver(uint16_t count) {

	/* the ifPlayGameOver variable is initialized in the function above */
	if (ifPlayGameOver) {

		/* counting the gameticks */
		uint8_t t = (count - playGameOverTick);

		/* if the gametick hits the 23, stop the game over sound */
		if (t == 23) {

			/* stop playing sound on the speaker */
			noTone(15);
			/* set the ifPlayGameOver variable to 0, to stop the game over function */
			ifPlayGameOver = 0;
			return;
		}

		/* stop playing sound on the speaker */
		noTone(15);

		/* play sound on the speaker using the notes from the gameOver array */
		tone(15, gameOver[t / 2], 83);
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

///* tempo of the notes */
//int musicTempo[] = {
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	4, // BREAK
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//	12, 12, 12, 12,
//
//	8, // END
//};

/* function to start the music */
void startMusic(uint16_t count) {
	ifPlayMusic = 1;
	playMusicTick = count;
}

/* function that contains the tones of the music */
void playMusic(uint16_t count) {

	/* the ifPlayMusic vaiabele is initialized in the function above */
	if (ifPlayMusic) {

		/* counting the gameticks */
		uint8_t t = (count - playMusicTick);

		/* if the gametick hits theh 323, stop the music */
		if (t == 323) {

			/* stop playing sound on the speaker */
			noTone(15);
			/* set the ifPlayMusic variable to 0, to stop the music function */
			ifPlayMusic = 0;
			return;
		}

		/* stop playing sound on the speaker */
		noTone(15);

		/* play sound on the speaker using the notes from the music array */
		tone(15, music[t / 2], 83);
	}

	///* size is used in the for loop to show the length of the song */
	//int size = sizeof(music) / sizeof(int);

	///* a for loop that plays the notes in the right order */
	//for (int note = 0; note < size; note++) {

	//	/* for the duration of the note, the tempo from musicTempo[] has to be devided
	//	by 1000 ms, a full note would be 1000 / 1, a half a note would be 1000 / 2 and
	//	a quarter of a note would be 1000 / 4 etc... */
	//	int noteDuration = 1000 / musicTempo[note];

	//	/* here the note is actually being played using the tone() function */
	//	tone(4, music[note], noteDuration);

	//	/* if you don't want the sound to become absolute rubbish, a delay should be
	//	put in, a delay of 100 seems to work well */
	//	_delay_ms(100);

	//	/* the noTone() function stops the tones being outputted */
	//	noTone(4);
	//}
}