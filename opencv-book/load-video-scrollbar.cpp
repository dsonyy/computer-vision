#include <opencv2/highgui.hpp>
#include "exercises.h"

int load_video() {
	cv::VideoCapture cap;
	cap.open("../res/video.mp4");
	
	cv::Mat frame;
	cv::namedWindow("example", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		cv::imshow("example", frame);
		cv::waitKey(cap.get(cv::CAP_PROP_FPS));
	}
	cv::destroyWindow("example");
	return 0;
}