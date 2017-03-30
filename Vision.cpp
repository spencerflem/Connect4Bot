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

	cv::threshold(blueThresh, blueThresh, 10, 255, 0);
	cv::floodFill(blueThresh, cv::Point(0,0), cv::Scalar(125));
	cv::threshold(blueThresh, blueThresh, 150, 0, cv::THRESH_TOZERO_INV);
	cv::threshold(blueThresh, blueThresh, 100, 255, cv::THRESH_BINARY_INV);
	showImg(blueThresh, "blu");

	int largest_area = 0;
	int largest_contour_index = 0;
	cv::Rect bounding_rect;

	std::vector<std::vector<cv::Point>> contours2; // Vector for storing contour
	std::vector<cv::Vec4i> hierarchy2;

	findContours(blueThresh, contours2, hierarchy2, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

	for (int i = 0; i< contours2.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours2[i], false);  //  Find the area of contour
		if (a>largest_area) {
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
			bounding_rect = cv::boundingRect(contours2[i]); // Find the bounding rectangle for biggest contour
		}

	}

	//drawContours(frame, contours2, largest_contour_index, cv::Scalar(255, 255, 255), CV_FILLED, 8, hierarchy2); // Draw the largest contour using previously stored index.
	//rectangle(frame, bounding_rect, cv::Scalar(0, 255, 0), 1, 8, 0);
	//showImg(frame, "biggest");

	std::vector<cv::RotatedRect> bestEllipses;
	cv::Mat ellipsed = cv::Mat::zeros(blueThresh.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		double closest = 99999999;
		double closestAfter = 99999999;
		for (int j = 0; j < contours.size(); j++) {
			if (i == j)
				continue;
			double dist = std::pow(minEllipse[i].center.x - minEllipse[j].center.x, 2) + std::pow(minEllipse[i].center.y - minEllipse[j].center.y, 2);
			if (dist < closest) {
				closest = dist;
				if (i < j)
					closestAfter = dist;
			}
		}
		//std::cout << "closest: " << closest << ", closestAfter: " << closestAfter << std::endl;
		cv::Scalar color;
		if (minEllipse[i].size.width >(bounding_rect.width / 20) && minEllipse[i].size.width < (bounding_rect.width / 6) && minEllipse[i].size.height >(bounding_rect.width / 20) && minEllipse[i].size.height < (bounding_rect.width / 6)) {
			color = cv::Scalar(100, 255, 100);
			if (closestAfter > std::pow(bounding_rect.width / 20, 2) && closest < std::pow(bounding_rect.width / 7, 2)) {
				bestEllipses.push_back(minEllipse[i]);
				color = cv::Scalar(255, 255, 255);
			}
		}
		else {
			color = cv::Scalar(80, 80, 80);
		}
		//std::cout << minEllipse[i].size.width << ", " << minEllipse[i].size.height << " vs " << bounding_rect.width << std::endl;
		ellipse(ellipsed, minEllipse[i], color, 2, 8);
	}

	std::cout << "numgood: " << bestEllipses.size() << std::endl;

	if (bestEllipses.size() == 42) {
		for (int i = 0; i < bestEllipses.size(); i++) {
			ellipse(frame, bestEllipses[i], cv::Scalar(255,255,255), 2, 8);
		}
		showImg(frame, "sucess");
	}


	//AFTER ALL THIS WORK< WAS IT EVEN NECESSARY?
	//CAN USE THE MASK, FILTER BY RED + YELLOW and COUNT
	//CIRCLES HAVE NO SENSE OF SCALE ATM, AND DO NOT CORRESPOND TO AN ARRAY
	//THIS IS A MAJOR PROBLEM 


	/// Show in a window
	showImg(ellipsed, "Ellipsed");

	return cv::Mat();
}
