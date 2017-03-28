#include "AI.h"
#include "Voice.h"
#include "Move.h"
#include "Game.h"
#include "Input.h"
#include <stdlib.h>
#include <time.h>

#ifdef VISION
#include "Vision.h"
#else
#include "Human.h"
#endif

using namespace std;


int main(int argc, char *argv[])
{
    srand ( time(NULL) );
    int finished = false;
    Move turn;
    Game playTime;
	#ifdef VISION
	Vision input = Vision();
	#else
	Human input = Human();
	#endif
	AI ai = AI(0);
    int player = 1;
    playTime.printBoard();
    while(!finished) {
		(player == 1) ? turn = ai.makeMove(playTime.getGameState(), player) : turn = input.getMove(player);
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
