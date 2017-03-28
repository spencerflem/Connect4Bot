#ifndef INPUT_H
#define INPUT_H

#include "Move.h"

class Input {
public:
	virtual Move getMove(int players) = 0;
};

#endif
