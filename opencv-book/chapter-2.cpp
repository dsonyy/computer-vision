#include "exercises.h"

int dummy() {

	return 0;
}
//-----------------------------------------------------------------------------
int load_image() {
	cv::Mat img;
	for (auto path : { "../res/lena.bmp", "./res/lena.bmp" }) {
		img = cv::imread(path);
		if (!img.empty())
			break;	
	}
	if (img.empty()) return 1;

	cv::namedWindow("example", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	cv::imshow("example", img);
	cv::waitKey(0);
	cv::destroyWindow("example");
	return 0;
}
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
namespace eh {
	cv::VideoCapture cap;
}

void slider_callback(int pos, void*) {
	auto a = eh::cap.set(cv::CAP_PROP_POS_FRAMES, pos);
}

int load_video_slider() {
	using eh::cap;
	int pos = 0;
	cap.open("../res/video.mp4");

	cv::Mat frame;
	cv::namedWindow("example", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("frame", "example", &pos, cap.get(cv::CAP_PROP_FRAME_COUNT), slider_callback);
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		int current_pos = int(cap.get(cv::CAP_PROP_POS_FRAMES));
		cv::setTrackbarPos("frame", "example", current_pos);
		cv::imshow("example", frame);
		char ch = cv::waitKey(cap.get(cv::CAP_PROP_FPS));
		if (ch == 'q') break;
	}
	cv::destroyWindow("example");
	return 0;
}
//-----------------------------------------------------------------------------
