#ifndef VISION_H
#define VISION_H

#include "Input.h"
#include "Move.h"
#include <opencv2/opencv.hpp>
#include <vector>

class Vision: public Input {
public:
	Vision();
	Move getMove(int player);
	//Returns moves made using a webcam
private:
	void showImg(cv::Mat frame, std::string name);
	cv::Mat threshByColor(cv::Mat frame, cv::Scalar lowRange, cv::Scalar highRange);
	cv::Mat findBoard(cv::Mat origFrame);
};

#endif
