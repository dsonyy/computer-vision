#include "exercises.h"

int chapter3() {

	auto n = -1922.1234;

	auto n0 = cv::abs(n);
	auto n1 = cvCeil(n0);
	auto n2 = cvRound(n0);
	auto n3 = cvFloor(n0);

	cv::Point2i p = cv::Point2f(12.1f, 100.1f);

	cv::Matx33f a = { 1,2,3, 1,2,3, 1,2,3 };
	cv::Vec3f b = { 1, 2, 3 };
	auto c = a * b;

	cv::Matx<char, 3, 3> aa;
	cv::Vec<char, 3> bb;
	auto cc = aa * bb;

	return 0;
}