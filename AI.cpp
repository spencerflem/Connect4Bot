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
	// double *availableColumns = getOptions(gameState);
	bool firstMove = true;
	for (int i = 0; i < COLUMN_COUNT_2; ++i) {
		if (gameState.board[ROW_COUNT_2-1][i] != 0)
			firstMove = false;
	}
	if (firstMove)
		return Move(player, 3);
	else {
		int strategy = rand() % 2;
		switch (strategy) {
			case 0: double *availableColumns = getOptions(gameState);
				int col = dangerSpot(gameState);
				if(col == -1) {
					do {
						col = rand() % 7;
					} while (availableColumns[col] != 3);
					delete availableColumns;
					return Move(player, col);
				}
				else {
					return Move(player, col);
				}
				break;
			case 1: return Move(player, decisiveAI(gameState));
		}
	}
	return Move(player, rand()%7);
}

double* AI::getOptions(GameState gameState) {
	double *options = new double[7];
	for (int i = 0; i < COLUMN_COUNT_2; ++i) {
		if (gameState.board[0][i] == 0)
			options[i] = 3; //a 3 denotes an available columns
		else
			options[i] = 0;
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

// TODO: It doesnt check diagonals, but that will be trivial to implement.
int AI::decisiveAI(GameState rows) { // 0 is nothing, 1 is AI, 2 is player, red is AI, yellow is player
	int randCol = rand() % 8;   // The AI chooses a random column (0-7) if the player is not about to win. Or if the AI is not about to win.


	// This will make the AI choose a column which is about to be taken by the player (IE, the player has three pieces in a vertical column already)
	for (int row = 6; row >= 3; row--)
	{
		for (int col = 0; col <= 7; col++)
		{
			if (rows.board[row][col] == 2 && rows.board[row - 1][col] == 2 && rows.board[row - 2][col] == 2 && rows.board[row - 3][col] == 0)
			{
				return col;
			}
		}
	}
	// This will make the AI choose a column it is about to win vertically. (IE the AI has three pieces in a vertical column already)
	for (int row = 6; row >= 3; row--)
	{
		for (int col = 0; col <= 7; col++)
		{
			if (rows.board[row][col] == 1 && rows.board[row - 1][col] == 1 && rows.board[row - 2][col] == 1 && rows.board[row - 3][col] == 0)
			{
				return col;
			}
		}
	}

	// This will make the AI choose a column which the player is about to win horizontally. (IE the player has three pieces in a horizontal row already)
	for (int col = 7; col >= 3; col--)
	{
		for (int row = 6; row >= 0; row--)
		{
			if (rows.board[row][col] == 2 && rows.board[row][col - 1] == 2 && rows.board[row][col - 2] == 2 && rows.board[row][col - 3] == 0)
			{
				return (col - 3);
			}
		}
	}

	// This will make the AI choose a column which the AI is about to win horizontally. (IE the AI has three pieces in a horizontal row already)
	for (int col = 7; col >= 3; col--)
	{
		for (int row = 6; row >= 0; row--)
		{
			if (rows.board[row][col] == 1 && rows.board[row][col - 1] == 1 && rows.board[row][col - 2] == 1 && rows.board[row][col - 3] == 0)
			{
				return (col - 3);
			}
		}
	}

	return randCol;

}
