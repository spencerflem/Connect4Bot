#include "Human.h"

Move Human::getMove(GameState gameState, int player) {
	std::cout << "player: " << player << std::endl;
	Move turn = Move();
	turn.player = player;
	std::cout << "Enter " << ((player == 1) ? "red" : "yellow") << " player's move column - ";
	std::cin >> turn.column;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	--turn.column;
	return turn;
}