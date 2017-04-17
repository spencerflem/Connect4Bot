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
<<<<<<< HEAD
=======
	int dangerSpot(GameState rows);
<<<<<<< HEAD
	int decisiveAI(GameState rows);
>>>>>>> refs/remotes/origin/master
=======
	int thomasAI(GameState rows);
>>>>>>> refs/remotes/origin/master
public:
	AI(int difficulty);
	int getDifficulty();
	bool setDifficulty(int difficulty);
	Move makeMove(GameState gameState, int player);
<<<<<<< HEAD
	int dangerSpot(GameState gameState);
=======

>>>>>>> refs/remotes/origin/master
};

#endif
