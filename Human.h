#ifndef HUMAN_H
#define HUMAN_H

#include "Input.h"
#include "Move.h"
#include "GameState.h"
#include <iostream>
#include <string>

class Human: public Input {
public:
	Move getMove(GameState gameState, int player);
	//Gathers move over terminal
};

#endif
