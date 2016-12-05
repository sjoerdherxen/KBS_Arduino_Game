#include "score.h"

/* array to store the scores in, 0 is skipped */
uint8_t scores[4];

/* function used to setup scores at the beginning of the game */
void setupScore() {
	/* for-loop that sets every score to 0 */
	for (int i = 0; i <= 4; i++) {
		scores[i] = 0;
	}
}

/* function to add score to a specific player,
needs an amount for points and a and a target player*/
void addScore(uint8_t points, int player) {
	/* the amount of points is given to the specified player */
	scores[player] = points;
}

/* function used to return the score of a specific player */
uint8_t returnScore(int player) {
	/* the score of teh specified player is returned */
	return scores[player];
}

