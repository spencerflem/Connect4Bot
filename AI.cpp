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

int AI::dangerSpot(GameState rows) {
	//This will return the column that the AI must play in to avoid a loss on the next turn.
	int dangerCol = -1;
	for(int i=0; i<ROW_COUNT_2; ++i) {
        for(int j=0; j<COLUMN_COUNT_2; ++j) {
            if(rows.board[i][j] != 0) {
                //Check row for 3 in a row condition
                if(j<=(COLUMN_COUNT_2-3) && (rows.board[i][j]==rows.board[i][j+1] && rows.board[i][j]==rows.board[i][j+2])) {
					//Check to see if the 3 in a row lies on the board's left border and is empty
					if(j!=0 && rows.board[i][j-1]==0) {
						//Check to see if the left side of the 3 in a row is a playable spot.
						if(i==ROW_COUNT_2-1) {
							return j-1;
						}
						else if(rows.board[i+1][j-1] != 0) {
							return j-1;
						}
					}
					//Check to see if the 3 in a row lies on the board's right border and is empty
					if(j!=COLUMN_COUNT_2-1 && rows.board[i][j+1]==0) {
						//Check to see if the right side of the 3 in a row is a playable spot.
						if(i==ROW_COUNT_2-1) {
							return j+1;
						}
						else if(rows.board[i+1][j+1] != 0) {
							return j+1;
						}
					}
                }
                //Check column for 3 in a row condition
                if(i<=(ROW_COUNT_2-3) && (rows.board[i][j]==rows.board[i+1][j] && rows.board[i][j]==rows.board[i+2][j])) {
					//Check to see if the 3 in a column lies below the board's top edge and if the space above is empty
					if(i!=0 && rows.board[i-1][j]==0) {
						return j;
					}
                }
				//Only check necessary positions for LDR condition
	            if(j<=(COLUMN_COUNT_2-3) && i<=(ROW_COUNT_2-3) && !(i==0 && j==4) && !(i==3 && j==0)) {
					//Check diagonal LDR for 3 in a diagonal condition
	                if(rows.board[i][j]==rows.board[i+1][j+1] && rows.board[i][j]==rows.board[i+2][j+2]) {
						//Check to see if left/up spot is dangerous
						if((i!=0 && j!=0) && rows.board[i-1][j-1]==0 && rows.board[i][j-1]!=0) {
							return j-1;
						}
						//Check to see if right/down spot is dangerous
						if((i!=3 && j!=4) && rows.board[i+3][j+3]==0) {
							if(i==2) {
								return j+3;
							}
							else if(rows.board[i+4][j+3]==0) {
								return j+3;
							}
						}
	                }
				}
				//Only check necessary positions for RDL condition
				if(j>=(COLUMN_COUNT_2-5) && i<=(ROW_COUNT_2-3) && !(i==0 && j==2) && !(i==3 && j==ROW_COUNT_2-1)) {
					//Check diagonal LDR for 3 in a diagonal condition
	                if(rows.board[i][j]==rows.board[i+1][j-1] && rows.board[i][j]==rows.board[i+2][j-2]) {
						//Check to see if right/up spot is dangerous
						if((i!=0 && j!=ROW_COUNT_2-1) && rows.board[i-1][j+1]==0 && rows.board[i][j+1]!=0) {
							return j+1;
						}
						//Check to see if left/down spot is dangerous
						if((i!=3 && j!=2) && rows.board[i+3][j-3]==0) {
							if(i==2) {
								return j-3;
							}
							else if(rows.board[i+4][j-3]==0) {
								return j-3;
							}
						}
	                }
				}
			}
        }
    }
	return dangerCol;
}
