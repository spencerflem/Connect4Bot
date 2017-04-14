#include "AI.h"
#include <stdlib.h>

AI::AI(int difficulty) {
	if(!setDifficulty(difficulty)) {
		setDifficulty(0);
	}
}

int AI::getDifficulty() {
	return difficulty;
}

bool AI::setDifficulty(int difficulty) {
	if(difficulty >= 0 && difficulty <= 2) {
		this->difficulty = difficulty;
		return true;
	}
	return false;
}

Move AI::makeMove(GameState gameState, int player) {
	double *availableColumns = getOptions(gameState);
	int location = -1;
	for (int i = 0; i < COLUMN_COUNT_2; ++i) {
		if (availableColumns[i] == 3)
			location = i;
	}
	if (location != -1)
		return Move(player, location);
	else
		return Move(player, rand()%7);
	//TODO getOptions and make a moveconsidering the options
	/*
		simple offensive AI:
		always pick the position with the most 1's surrounding it.

		makes no attempt at stopping the player from completing a connect 4

		simple defensive AI:
		always pick the next empty spot in a column with two or more "exposed" 2's,
		or position in a row with two or more "exposed" 2's, excluding positions in
		columns 1 and 7.

		has no defense against diagonal connects.
		does not make offensive moves, thus bound to lose.

		whimsical simple AI:
		randomly chooses either a simple defensive or simple offensive move.

		effectiveness unknown.

		complex AI: ???read a tutorial???
	*/

}

double* AI::getOptions(GameState gameState) {
	double *options = new double[7];
	int taken = 0;
	for (int i = 0; i < COLUMN_COUNT_2; ++i) {
		for (int j = 0; j < ROW_COUNT_2; ++j) {
			if (gameState.board[j][i] != 0)
				taken++;
		}
		if (taken == 0)
			options[i] = 3; //a 3 denotes an available column...for now
		options[i] = 0;
		taken = 0;
	}
	return options;
}
