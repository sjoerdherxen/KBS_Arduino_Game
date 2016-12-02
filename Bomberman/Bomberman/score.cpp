#include "score.h"

/* makes an integer for the score of every player,
player 3 and 4 are optional and not in the game yet */
uint8_t scorePlayer1, scorePlayer2, scorePlayer3, scorePlayer4;

/* function used to setup scores at the beginning of the game */
void setupScore() {
	/* sets score of player 1 to 0 */
	scorePlayer1 = 0;

	/* sets score of player 2 to 0 */
	scorePlayer2 = 0;

	/* sets score of player 3 to 0 (UNUSED) */
	scorePlayer3 = 0;

	/* sets scroe of player 4 to 0 (UNUSED) */
	scorePlayer4 = 0;
}

/* function to add score to a specific player,
needs an amount for points and a and a target player*/
void addScore(uint8_t points, int player) {
	
	/* switch case to look which player is the target for the score */
	switch (player) {

		/* case 1 is equal to player 1 */
	case 1 :
		scorePlayer1 += points;

		/* the switch case terminates when the case hits this break */
		break;

		/* case 2 is equal to player 2 */
	case 2 :
		scorePlayer2 += points;

		/* the switch case terminates when the case hits this break */
		break;

		/* case 3 is equal to player 3 */
	case 3 :
		scorePlayer3 += points;

		/* the switch case terminates when the case hits this break */
		break;

		/* case 4 is equal to player 4 */
	case 4 :
		scorePlayer4 += points;

		/* the switch case terminates when the case hits this break */
		break;
	}
}

/* function used to return the score of a specific player */
uint8_t returnScore(int player) {
	
	/* switch case to determine which score has to be returned */
	switch (player) {

	/* case 1 is equal to player 1 */
	case 1 : 
		return scorePlayer1;

		/* the switch case terminates when the case hits this break */
		break;

	/* case 2 is equal to player 2 */
	case 2 :
		return scorePlayer2;

		/* the switch case terminates when the case hits this break */
		break;

	/* case 3 is equal to player 3 */
	case 3 :
		return scorePlayer3;

		/* the switch case terminates when the case hits this break */
		break;

	/* case 4 is equal to player 4 */
	case 4 :
		return scorePlayer4;

		/* the switch case terminates when the case hits this break */
		break;
	}
}

