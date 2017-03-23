#include "Vision.h"
#include "AI.h"
#include "Voice.h"
#include "Move.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
	srand ( time(NULL) );
	GameState gameState = GameState();
	Vision vision = Vision();
	Move move = vision.getMove();
	std::cout << move.player << ", " << move.column <<std::endl;
	move = vision.getMove();
	std::cout << move.player << ", " << move.column <<std::endl;
	move = vision.getMove();
	std::cout << move.player << ", " << move.column <<std::endl;
	move = vision.getMove();
	std::cout << move.player << ", " << move.column <<std::endl;
	std::cout << std::endl;
	AI ai = AI(0);
	move = ai.makeMove(gameState);
	std::cout << move.player << ", " << move.column <<std::endl;
	move = ai.makeMove(gameState);
	std::cout << move.player << ", " << move.column <<std::endl;
	move = ai.makeMove(gameState);
	std::cout << move.player << ", " << move.column <<std::endl;
	move = ai.makeMove(gameState);
	std::cout << move.player << ", " << move.column <<std::endl;
	Voice voice = Voice();
	voice.speak("test1");
	voice.speak("test2");
	voice.speak("test3");
	voice.speak("test4");
	
	return 0;
}
