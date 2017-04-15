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
	int col;
	do {
		col = rand() % 7;
	} while (availableColumns[col] != 3);
	return Move(player, col);
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
		if (taken < ROW_COUNT_2)
			options[i] = 3; //a 3 denotes an available column...for now
		else
			options[i] = 0;
		taken = 0;
	}
	return options;
}

int* AI::threeInARow(GameState GameState) {
	int *arr = new int[2];
	arr[0] = -1;
	arr[1] = -1;
	for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            if(rows[i][j] != 0) {
                //Check row? for win condition
                if(j<=(COLUMN_COUNT-3) && (rows[i][j]==rows[i][j+1] && rows[i][j]==rows[i][j+2])) {
					arr[0] = i;
					arr[1] = j;
                    return arr;
                }
                //Check column? for win condition
                else if(i<=(ROW_COUNT-3) && (rows[i][j]==rows[i+1][j] && rows[i][j]==rows[i+2][j])) {
					arr[1] = i;
					arr[0] = j;
                    return arr;
                }
            }
            /*//Check diagonal for win condition
            if(j<=3) {
                if(diagLDR[i+3][j]!=0 && (diagLDR[i+3][j]==diagLDR[i+3][j+1] && diagLDR[i+3][j]==diagLDR[i+3][j+2])) {
                    return arr;
                }
                if(diagRDL[i+3][j]!=0 && (diagRDL[i+3][j]==diagRDL[i+3][j+1] && diagRDL[i+3][j]==diagRDL[i+3][j+2])) {
                    return arr;
                }
            }*/
        }
    }
}
