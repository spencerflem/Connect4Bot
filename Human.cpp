#include "Human.h"

Move Human::getMove(GameState gameState, int player) {
	std::cout << "player: " << player << std::endl;
	Move turn = Move();
	turn.player = player;
	output.promptMove(player);
	std::cin >> turn.column;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	--turn.column;
	return turn;
}