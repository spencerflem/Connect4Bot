#include "Vision.h"

#include <stdlib.h>

Vision::Vision() {}

Move Vision::getMove(int player) {
	cv::VideoCapture capture("C:\\Users\\me\\Pictures\\Camera Roll\\vid3.mp4"); //replace string with 0 to get webcam
	//cv::VideoCapture capture(0);

	if (!capture.isOpened()) {
		throw "TODO: REAL EXCEPTION";
	}

	while (true) {
		cv::Mat frame;
		capture.read(frame);
		cv::imshow("cam", frame);
		cv::Mat board = findBoard(frame);
		findBoard(frame);
		cv::waitKey(10);
	}

	return Move((rand()%2) +1, rand()%7);
}

void Vision::showImg(cv::Mat frame, std::string name) {
	while (true) {
		cv::imshow(name, frame);
		if (cv::waitKey(10))
			break;
	}
}

//is this even necessary?
cv::Mat Vision::threshByColor(cv::Mat frame, cv::Scalar lowRange, cv::Scalar highRange) {
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
	cv::inRange(hsvFrame, lowRange, highRange, hsvFrame);
	return hsvFrame;
}

cv::Mat Vision::findBoard(cv::Mat origFrame) {
	cv::Mat frameBig = origFrame.clone();
	cv::Mat frame;
	cv::resize(frameBig, frame, cv::Size(), 0.5, 0.5);
	//cv::Mat blueThresh, gray; cv::cvtColor(frame, gray, CV_BGR2GRAY); cv::threshold(gray, blueThresh, 10, 255, 0);
	cv::Mat blueThresh = threshByColor(frame, cv::Scalar(100, 155, 65), cv::Scalar(150, 255, 255)); //thresh blue only, numbers found experimentally
	cv::Mat watersheder = blueThresh.clone();
																									//very important, will not work without blur whatsoever - todo: find out why?
	GaussianBlur(blueThresh, blueThresh, cv::Size(15, 15), 2, 2); //Gaussian blur - size left unchanged from cv documentation

	cv::Mat canny_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using canny
	int thresh = 100;
	Canny(blueThresh, canny_output, thresh, thresh * 2, 3);

	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/// Find the rotated rectangles and ellipses for each contour
	std::vector<cv::RotatedRect> minEllipse(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > 5) {
			minEllipse[i] = cv::fitEllipse(cv::Mat(contours[i]));
		}
	}

	/// Draw contours + rotated rects + ellipses
	cv::Mat ellipsed = cv::Mat::zeros(blueThresh.size(), CV_8UC3);
	cv::Rect boundingRect;
	for (int i = 0; i< contours.size(); i++) {
		ellipse(ellipsed, minEllipse[i], cv::Scalar(255, 255, 255), 2, 8);
	}

	/// Show in a window
	showImg(ellipsed, "Ellipsed");

	cv::threshold(blueThresh, blueThresh, 10, 255, 0);
	return cv::Mat();
}
