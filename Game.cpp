#include "Vision.h"
#include "AI.h"
#include "Voice.h"
#include "Move.h"
#include "Game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>


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
void Game::takeTurn(Play* turn) {
    int pos = -1;
    if(columns[turn->moveColumn][ROW_COUNT-1]==0) {
        pos=ROW_COUNT-1;
        cout << "MEME" <<endl;
    }
    else while(columns[turn->moveColumn][pos+1]==0) {
        pos++;
    }
    if(pos==-1) {
        cout << "Error: Column full";
        return;
    }
    columns[turn->moveColumn][pos] = turn->playerID;
    rows[pos][turn->moveColumn] = turn->playerID;
    diagonal_left_down_right[turn->moveColumn+(5-pos)][turn->moveColumn] = turn->playerID;
    diagonal_right_down_left[(6-turn->moveColumn)+(5-pos)][6-turn->moveColumn] = turn->playerID;
}

bool Game::isWin() {
    //TODO
    return true;
}

int main()
{
    /*cout << "Welcome! Will you be playing with a webcam? (Y/N) - ";
    string webcam = "";
    cin >> webcam;*/
    //TODO Webcam implementation
    bool finished = false;
    Game playTime;
    while(!finished) {
        playTime.printBoard();

        Play* turn1 = new Play;
        turn1->playerID=1;
        cout << "Enter red player's move column - ";
        cin >> turn1->moveColumn;
        --turn1->moveColumn;
        playTime.takeTurn(turn1);
        playTime.printBoard();

        Play* turn2 = new Play;
        turn2->playerID=2;
        cout << "Enter yellow player's move column - ";
        cin >> turn2->moveColumn;
        --turn2->moveColumn;
        playTime.takeTurn(turn2);

        playTime.printBoard();
        finished = playTime.isWin();
    }
    return 0;
}
