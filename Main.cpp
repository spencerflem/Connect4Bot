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
    int finished = false;
    Move turn;
    Game playTime;
    int player = 1;
    playTime.printBoard();
    while(!finished) {
        turn = Move();
        turn.player=player;
        cout << "Enter " << ((player==1)? "red" : "yellow") << " player's move column - ";
        cin >> turn.column;
        --turn.column;
        if (playTime.takeTurn(turn)) {
			(player==1)? player++ : player--;
		}
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
