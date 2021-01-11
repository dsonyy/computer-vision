#include "exercises.h"

int drawing_shapes() {
	cv::Size sz(500, 500);
	cv::Mat_<cv::Vec3b> mat(sz, cv::Vec3f::all(0));
	cv::namedWindow("example", cv::WINDOW_AUTOSIZE);

	cv::circle(mat, cv::Point(sz / 2), 100, cv::Scalar(0, 255, 0), 0, 8);

	cv::imshow("example", mat);
	cv::waitKey();
	return 0;
}