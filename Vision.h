#ifndef VISION_H
#define VISION_H

#include "Input.h"
#include "Move.h"
#include <opencv2/opencv.hpp>

class Vision: public Input {
public:
	Vision();
	Move getMove(int player);
};

#endif
