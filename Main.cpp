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
    Move turn1;
    Move turn2;
    Game playTime;
    playTime.printBoard();
    int finished = 0;
    while(finished==0) {
        turn1 = Move();
        turn1.player=1;
        cout << "Enter red player's move column - ";
        cin >> turn1.column;
        --turn1.column;
        playTime.takeTurn(turn1);
        playTime.printBoard();
        finished = playTime.isWin();
        if(finished!=0){
            break;
        }

        turn2 = Move();
        turn2.player=2;
        cout << "Enter yellow player's move column - ";
        cin >> turn2.column;
        --turn2.column;
        playTime.takeTurn(turn2);
        playTime.printBoard();
        finished = playTime.isWin();
        cout << finished <<endl;
    }
    string color = "";
    if(finished == 1) {
        color = "Red";
    }
    else if(finished == 2){
        color = "Yellow";
    }
    cout << color << " player has won the game!" << endl;
    return 0;
}
