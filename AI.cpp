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
	int board* = gameState; //just because pointers
	new options[7] = {0,0,0,0,0,0,0}; //array to be returned, index of open colums
	int taken = 0; //counter for number of
	for (int i = 0; i < COLUMN_COUNT; ++i) {
		for (int j = 0; j < ROW_COUNT; ++j) {
			if (board[j][i] != 0)
				taken++; //increments for each place taken in a column
		}
		if (taken == 0)
			options[i] = 3; //a 3 denotes an available column...for now
		taken = 0;
	}
	return options; //an int array with a 3 denoting an open column
}
