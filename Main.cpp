#include "AI.h"
#include "Move.h"
#include "Game.h"
#include "Input.h"
#include "Output.h"
#include <stdlib.h>
#include <time.h>

#ifdef VISION
#include "Vision.h"
const bool vision = true;
#else
#include "Human.h"
const bool vision = false;
#endif

#ifdef VOICE
#include "Voice.h"
const bool voice = true;
#else
#include "Text.h"
const bool voice = false;
#endif

int main(int argc, char *argv [])
{
	srand(time(NULL));
	int finished = false;
	Move turn;
	Game game;
	#ifdef VISION
		Vision input = Vision();
	#else
		Human input = Human();
	#endif
	#ifdef VOICE
		Voice output = Voice();
	#else
		Text output = Text();
	#endif
	AI ai = AI(0);
	int player = 1;
	while (!finished) {
		if (player == 1) {
			turn = ai.makeMove(game.getGameState(), player);
			if (vision) {
				output.requestMove(turn.column + 1);
				Move playerTurn = input.getMove(game.getGameState(), player);
				if (playerTurn != turn) {
					output.badMove();
					return -1; //more graceful way?
				}
			}
		}
		else {
			turn = input.getMove(game.getGameState(), player);
			if (turn.player != player) {
				output.badMove();
				return -1; //more graceful way?
			}
		}
		if (game.takeTurn(turn)) {
			if (player == 1) {
				player++;
				output.printBoard(game.getGameState());
			}
			else {
				player--;
			}
		}
		finished = game.isWin();
	}
	if (finished > 1) {
		output.printBoard(game.getGameState());
	}
	output.announceWinner(finished);

	return 0;
}
