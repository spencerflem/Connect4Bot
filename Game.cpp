#include "Game.h"

Game::Game() {
    for(int i=0; i<COLUMN_COUNT; ++i) {
        for(int j=0; j<ROW_COUNT; ++j) {
            columns[i][j] = 0;
        }
    }
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            rows[i][j] = 0;
        }
    }
    for(int i=0; i<DIAGONAL_COUNT; ++i) {
        for(int j=0; j<DIAGONAL_COUNT; ++j) {
            diagLDR[i][j] = 0;
            diagRDL[i][j] = 0;
        }
    }
}

void Game::printBoard() {
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            std::cout << "|   " << rows[i][j] << "   ";
        }
        std::cout << "|" << std::endl;
        std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    }
}

bool Game::takeTurn(Move turn) {
	if(turn.column < 0 || turn.column >= COLUMN_COUNT) {
		std::cout << "Error: Illegal Move" << std::endl;
        return false;
	}
    int pos = -1;
    if(columns[turn.column][ROW_COUNT-1]==0) {
        pos=ROW_COUNT-1;
    }
    else while(columns[turn.column][pos+1]==0) {
        pos++;
    }
    if(pos==-1) {
        std::cout << "Error: Column full" << std::endl;
        return false;
    }
    columns[turn.column][pos] = turn.player;
    rows[pos][turn.column] = turn.player;
    diagLDR[turn.column+(ROW_COUNT-pos-1)][turn.column] = turn.player;
    diagRDL[(COLUMN_COUNT-turn.column-1)+(ROW_COUNT-pos-1)][COLUMN_COUNT-turn.column-1] = turn.player;
    return true;
}

int Game::isWin() {
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            if(rows[i][j] != 0) {
                //Check rows for win condition
                if(j<=3 && (rows[i][j]==rows[i][j+1] && rows[i][j]==rows[i][j+2] && rows[i][j]==rows[i][j+3])) {
                    return rows[i][j];
                }
                //Check column for win condition
                else if(i<=2 && (rows[i][j]==rows[i+1][j] && rows[i][j]==rows[i+2][j] && rows[i][j]==rows[i+3][j])) {
                    return rows[i][j];
                }
            }
            //Check diagonal for win condition
            if(j<=2) {
                if(diagLDR[i+3][j]!=0 && (diagLDR[i+3][j]==diagLDR[i+3][j+1] && diagLDR[i+3][j]==diagLDR[i+3][j+2] && diagLDR[i+3][j]==diagLDR[i+3][j+3])) {
                    return diagLDR[i+3][j];
                }
                if(diagRDL[i+3][j]!=0 && (diagRDL[i+3][j]==diagRDL[i+3][j+1] && diagRDL[i+3][j]==diagRDL[i+3][j+2] && diagRDL[i+3][j]==diagRDL[i+3][j+3])) {
                    return diagRDL[i+3][j];
                }
            }
        }
    }
    return 0;
}

GameState Game::getGameState() {
    GameState gs;
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            gs.board[i][j] = rows[i][j];
        }
    }
    return gs;
}
