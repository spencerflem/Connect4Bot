#include "Vision.h"
#include "AI.h"
#include "Voice.h"
#include "Move.h"
#include "Game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

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
    cout << "###########################################" << endl;
    for(int i=0; i<ROW_COUNT; ++i) {
        for(int j=0; j<COLUMN_COUNT; ++j) {
            cout << "#  " << rows[i][j] << "  ";
        }
        cout << "#" << endl;
        cout << "###########################################" << endl;
    }
}

void Game::takeTurn(Move turn) {
    int pos = -1;
    if(columns[turn.column][ROW_COUNT-1]==0) {
        pos=ROW_COUNT-1;
        cout << "MEME" <<endl;
    }
    else while(columns[turn.column][pos+1]==0) {
        pos++;
    }
    if(pos==-1) {
        cout << "Error: Column full";
        return;
    }
    columns[turn.column][pos] = turn.player;
    rows[pos][turn.column] = turn.player;
    diagonal_left_down_right[turn.column+(5-pos)][turn.column] = turn.player;
    diagonal_right_down_left[(6-turn.column)+(5-pos)][6-turn.column] = turn.player;
}

bool Game::isWin() {
    //TODO
    return false;
}

int main()
{
    /*cout << "Welcome! Will you be playing with a webcam? (Y/N) - ";
    string webcam = "";
    cin >> webcam;*/
    //TODO Webcam implementation
    bool finished = false;
    Move turn1;
    Move turn2;
    Game playTime;
    playTime.printBoard();
    while(!finished) {
        turn1 = Move();
        turn1.player=1;
        cout << "Enter red player's move column - ";
        cin >> turn1.column;
        --turn1.column;
        playTime.takeTurn(turn1);
        playTime.printBoard();

        turn2 = Move();
        turn2.player=2;
        cout << "Enter yellow player's move column - ";
        cin >> turn2.column;
        --turn2.column;
        playTime.takeTurn(turn2);

        playTime.printBoard();
        finished = playTime.isWin();
    }
    return 0;
}
