#ifndef VOICE_H
#define VOICE_H

#include "Output.h"
#include "GameState.h"
#include <windows.h>
#include <mmsystem.h>

class Voice : public Output {
public:
	Voice() {}
	void printBoard(GameState gameState);
	void badMove();
	void requestMove(int column);
	void announceWinner(int player);
	void visionError();
	void promptMove(int player);
};

#endif