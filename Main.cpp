#include "Vision.h"
#include "AI.h"
#include "Voice.h"
#include "Move.h"
#include "Game.h"
#include "Game.cpp"
#include <stdlib.h>
#include <time.h>

using namespace std;


int main()
{
    /*cout << "Welcome! Will you be playing with a webcam? (Y/N) - ";
    string webcam = "";
    cin >> webcam;*/
    //TODO Webcam implementation
    srand ( time(NULL) );
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
