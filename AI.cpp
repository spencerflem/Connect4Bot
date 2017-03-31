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
	return Move(player, rand()%7);//TODO getOptions and make a moveconsidering the options
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
	return new double[7];
	//TODO traverse the array and return the numbers of non-Full columns
}
