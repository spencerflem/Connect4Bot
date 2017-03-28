#ifndef HUMAN_H
#define HUMAN_H

#include "Input.h"
#include "Move.h"
#include <iostream>
#include <string>

class Human: public Input {
public:
	Move getMove(int player);
};

#endif
