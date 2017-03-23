#include "Game.h"

Game::Game()
{
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
            diagonal_left_down_right[i][j] = 0;
            diagonal_right_down_left[i][j] = 0;
        }
    }
}

void Game::printBoard() {
    std::cout << "###########################################" << std::endl;
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            std::cout << "#  " << rows[i][j] << "  ";
        }
        std::cout << "#" << std::endl;
        std::cout << "###########################################" << std::endl;
    }
}

bool Game::takeTurn(Move turn) {
    int pos = -1;
    if(columns[turn.column][ROW_COUNT-1]==0) {
        pos=ROW_COUNT-1;
        std::cout << "MEME" <<std::endl;
    }
    else while(columns[turn.column][pos+1]==0) {
        pos++;
    }
    if(pos==-1) {
        std::cout << "Error: Column full";
        return false;
    }
    columns[turn.column][pos] = turn.player;
    rows[pos][turn.column] = turn.player;
    diagonal_left_down_right[turn.column+(5-pos)][turn.column] = turn.player;
    diagonal_right_down_left[(6-turn.column)+(5-pos)][6-turn.column] = turn.player;
    return true;
}

bool Game::isWin() {
    //TODO
    return false;
}
