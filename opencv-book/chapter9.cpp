#include "exercises.h"

int window_move_spam() {
	cv::Mat mat = cv::imread("../res/lena.bmp");
	int n = 10;
	for (int i = 0; i < n; i++) {
		cv::namedWindow("lena" + std::to_string(i), cv::WINDOW_AUTOSIZE);
	}

	while (true) {
		for (int i = 0; i < n; i++) {
			cv::Point pos = { rand() % 6000 - 2000, rand() % 1000 };
			cv::moveWindow("lena" + std::to_string(i), pos.x, pos.y);
			cv::imshow("lena" + std::to_string(i), mat);
		}
		if ('q' == cv::waitKey(10)) break;
	}
	return 0;
}

int window_overlay() {
	cv::Mat mat = cv::imread("../res/lena.bmp");
	cv::namedWindow("lena", cv::WINDOW_AUTOSIZE);
	cv::imshow("lena", mat);
	cv::displayOverlay("lena", "Szymon Bednorz");

	while (true) {	
		if ('q' == cv::waitKey(10)) break;
	}

	return 0;
}