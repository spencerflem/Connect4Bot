#include "Vision.h"

#include <stdlib.h>

Vision::Vision() {}

Move Vision::getMove() {
	return Move((rand()%2) +1, rand()%7);
}
