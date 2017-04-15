#ifndef AI_H
#define AI_H

#include "Move.h"
#include "GameState.h"

const int COLUMN_COUNT_2 = 7; //these should be moved to somewhere centralized
const int ROW_COUNT_2 = 6;

class AI {
private:
	int difficulty;
	double* getOptions(GameState gameState);
	int dangerSpot(GameState gameState);
public:
	AI(int difficulty);
	int getDifficulty();
	bool setDifficulty(int difficulty);
	Move makeMove(GameState gameState, int player);
};

#endif
