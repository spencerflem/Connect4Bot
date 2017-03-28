#include "Vision.h"

#include <stdlib.h>

Vision::Vision() {}

Move Vision::getMove(int player) {
	cv::VideoCapture capture("C:\\Users\\me\\Pictures\\Camera Roll\\vid3.mp4"); //replace string with 0 to get webcam

	if (!capture.isOpened()) {
		throw "TODO: REAL EXCEPTION";
	}

	while (true) {
		cv::Mat frame;
		capture.read(frame);
		cv::imshow("cam", frame);
		cv::waitKey(30);
	}

	return Move((rand()%2) +1, rand()%7);
}
