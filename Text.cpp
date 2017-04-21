#include "Text.h"

void Text::printBoard(GameState gameState) {
	std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	for (int i = 0; i<6; ++i) {
		for (int j = 0; j<7; ++j) {
			std::cout << "|   ";
			if(gameState.board[i][j] == 1) {
				std::cout << "\033[1;31mO\033[0m";
			}
			else if(gameState.board[i][j]==2) {
				std::cout << "\033[1;33mO\033[0m";
			}
			else if(gameState.board[i][j]==0) {
				std::cout << " ";
			}
			std::cout << "   ";
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
		std::cout << "Red Player has won the game!" << std::endl;
	}
	else if (player == 2) {
		std::cout << "Yellow Player has won the game!" << std::endl;
	}
	else {
		std::cout << "Stalemate!" << std::endl;
	}
}

void Text::visionError() {
	std::cout << "Vision Error" << std::endl;
}

void Text::promptMove(int player) {
	std::cout << std::endl << "Enter " << ((player == 1) ? "Red" : "Yellow") << " Player's move column: ";
}
