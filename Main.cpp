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
    Game game;
	#ifdef VISION
	Vision input = Vision();
	const bool vision = true;
	#else
	Human input = Human();
	const bool vision = false;
	#endif
	AI ai = AI(0);
    int player = 1;
    game.printBoard();
    while(!finished) {
		if (player == 1) {
			turn = ai.makeMove(game.getGameState(), player);
			if (vision) {
				std::cout << "Please play in column " << turn.column+1 << std::endl;
				Move playerTurn = input.getMove(game.getGameState(), player);
				if (playerTurn != turn) {
					std::cout << "YOU PLAYED " << ((playerTurn.player==1)? "RED" : "YELLOW") << " COLUMN " << playerTurn.column+1 << " NOT " << ((turn.player == 1) ? "RED" : "YELLOW") << " COLUMN " << turn.column+1 << std::endl;
					return -1; //more graceful way?
				}
			}
		}
		else {
			turn = input.getMove(game.getGameState(), player);
			if (turn.player != player) {
				std::cout << "YOU PLAYED THE WRONG COLOR, DUMMY" << std::endl;
				return -1; //more graceful way?
			}
		}
        if (game.takeTurn(turn)) {
			(player==1)? player++ : player--;
		}
        game.printBoard();
        finished = game.isWin();
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