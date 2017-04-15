#include "Voice.h"

#include "Text.h" //temp
void Voice::printBoard(GameState gameState) {
	Text text = Text();
	text.printBoard(gameState);
}

void Voice::badMove() {
	Text text = Text();
	text.badMove();
	PlaySound(TEXT("audio/badmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::requestMove(int column) {
	Text text = Text();
	text.requestMove(column);
	PlaySound(TEXT("audio/requestmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
	const char *filename = ("audio/col" + std::to_string(column) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);

}

void Voice::announceWinner(int player) {
	Text text = Text();
	text.announceWinner(player);
	const char *filename = ("audio/player" + std::to_string(player) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("audio/wins.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::visionError() {
	Text text = Text();
	text.visionError();
	PlaySound(TEXT("audio/visionerror.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}

void Voice::promptMove(int player) {
	Text text = Text();
	text.promptMove(player);
	const char *filename = ("audio/player" + std::to_string(player) + ".wav").c_str();
	PlaySound(TEXT(filename), NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("audio/promptmove.wav"), NULL, SND_ALIAS | SND_APPLICATION);
}