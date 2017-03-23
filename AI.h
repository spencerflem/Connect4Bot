#ifndef AI_H
#define AI_H

#include "Move.h"

class AI {
private:
	int difficulty;
	double* getOptions(GameState gameState);
public:
	AI(int difficulty);
	int getDifficulty();
	bool setDifficulty(int difficulty);
	Move makeMove(GameState gameState);
};

#endif
