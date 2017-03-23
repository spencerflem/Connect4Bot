#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

const int COLUMN_COUNT = 7;
const int ROW_COUNT = 6;
const int DIAGONAL_COUNT = 11;
const int DIAGONAL_LENGTH = 6;
struct Play {
    //Player 1 = Red
    //Player 2 = Yellow
    int playerID;
    int moveColumn;
    int moveRow;
};

class Game
{
    public:
        Game();
        //Prints the current board state
        void printBoard();
        //Makes a move and updates board
        void takeTurn(Play* turn);
        //Checks to see if a player has won the game
        bool isWin();
    private:
        int columns[COLUMN_COUNT][ROW_COUNT];
        int rows[ROW_COUNT][COLUMN_COUNT];
        int diagonal_left_down_right[DIAGONAL_COUNT][DIAGONAL_LENGTH];
        int diagonal_right_down_left[DIAGONAL_COUNT][DIAGONAL_LENGTH];
};

#endif // GAME_H
