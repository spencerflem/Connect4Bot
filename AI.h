#ifndef AI_H
#define AI_H

#include "Move.h"
#include "GameState.h"
#include <cmath>

const int COLUMN_COUNT_2 = 7; //these should be moved to somewhere centralized
const int ROW_COUNT_2 = 6;

class AI {
private:
	int difficulty;
	double* getOptions(GameState gameState);
	int dangerSpot(GameState rows);
<<<<<<< HEAD
=======
	int thomasAI(GameState rows);
	int loopDepth=0;
>>>>>>> refs/remotes/origin/master
public:
	AI(int difficulty);
	int thomasAI(GameState rows);
	int getDifficulty();
	bool setDifficulty(int difficulty);
	Move makeMove(GameState gameState, int player);
};

#endif
