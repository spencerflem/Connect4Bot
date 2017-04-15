#include "Voice.h"

void Voice::printBoard(GameState gameState) {
	text.printBoard(gameState);
}

void Voice::badMove() {
	text.badMove();
	PlaySound(TEXT("audio/badmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::requestMove(int column) {
	text.requestMove(column);
	PlaySound(TEXT("audio/requestmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
	const char *filename = ("audio/col" + std::to_string(column) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);

}

void Voice::announceWinner(int player) {
	text.announceWinner(player);
	const char *filename = ("audio/player" + std::to_string(player) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("audio/wins.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::visionError() {
	text.visionError();
	PlaySound(TEXT("audio/visionerror.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::promptMove(int player) {
	text.promptMove(player);
	const char *filename = ("audio/player" + std::to_string(player) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("audio/promptmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}