#include "Text.h"

void Text::printBoard(GameState gameState) {
	std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	for (int i = 0; i<6; ++i) {
		for (int j = 0; j<7; ++j) {
			std::cout << "|   " << gameState.board[i][j] << "   ";
		}
		std::cout << "|" << std::endl;
		std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	}
}

void Text::badMove() {
	std::cout << "INVALID MOVE" << std::endl;
}

void Text::requestMove(int column) {
	std::cout << "Please play in column " << column << std::endl;
}

void Text::announceWinner(int player) {
	if (player == 1) {
		std::cout << "Red player has won the game!" << std::endl;
	}
	else if (player == 2) {
		std::cout << "Yellow player has won the game!" << std::endl;
	}
	else {
		std::cout << "Stalemate!" << std::endl;
	}
}

void Text::visionError() {
	std::cout << "Vision Error" << std::endl;
}

void Text::promptMove(int player) {
	std::cout << "Enter " << ((player == 1) ? "red" : "yellow") << " player's move column - ";
}
