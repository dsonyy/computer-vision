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

		char ch = cv::waitKey(1000 / cap.get(cv::CAP_PROP_FPS));
		if (ch == 'q') break;
	}
	cv::destroyWindow("example");
	return 0;
}

//-----------------------------------------------------------------------------
namespace eh {
	cv::VideoCapture cap;
}

void slider_callback(int pos, void*) {
	eh::cap.set(cv::CAP_PROP_POS_FRAMES, pos);
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
		char ch = cv::waitKey(1000 / cap.get(cv::CAP_PROP_FPS));
		if (ch == 'q') break;
	}
	cv::destroyWindow("example");
	return 0;
}
//-----------------------------------------------------------------------------
int read_camera() {
	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		return 1;
	}

	cv::Mat frame;
	cv::namedWindow("example", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	for (;;) {
		cap.read(frame);
		if (frame.empty()) break;
		cv::imshow("example", frame);
		char ch = cv::waitKey(1);
		if (ch == 'q') break;
	}
	return 0;
}
//-----------------------------------------------------------------------------
int save_video() {
	cv::VideoCapture cap;
	cap.open("../res/video.mp4");

	cv::VideoWriter writer("output.avi",
		cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 
		cap.get(cv::CAP_PROP_FPS), 
		cv::Size(
			cap.get(cv::CAP_PROP_FRAME_WIDTH), 
			cap.get(cv::CAP_PROP_FRAME_HEIGHT)
		)
	);

	cv::Mat frame;
	cv::namedWindow("example", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	int X = 0, Y = 0;
	cv::createTrackbar("X", "example", &X, cap.get(cv::CAP_PROP_FRAME_WIDTH));
	cv::createTrackbar("Y", "example", &Y, cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;

		cv::logPolar(frame, frame, cv::Point2f(X, Y), 40, cv::WARP_FILL_OUTLIERS);
		cv::drawMarker(frame, cv::Point(X, Y), cv::Scalar(0, 0, 255, 0), cv::MARKER_CROSS);

		cv::imshow("example", frame);
		writer << frame;

		char ch = cv::waitKey(1000 / cap.get(cv::CAP_PROP_FPS));
		if (ch == 'q') break;
	}
	cv::destroyWindow("example");
	return 0;
}
//-----------------------------------------------------------------------------
int read_save_camera() {
	cv::VideoCapture cap(0);
	cv::VideoWriter writer("output2.avi",
		cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
		cap.get(cv::CAP_PROP_FPS),
		cv::Size(
			(cap.get(cv::CAP_PROP_FRAME_WIDTH) + 1) / 2,
			(cap.get(cv::CAP_PROP_FRAME_HEIGHT) + 1) / 2
			)
		);

	cv::Mat frame1, frame2;
	cv::namedWindow("frame 1", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	cv::namedWindow("frame 2", cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
	for (;;) {
		cap >> frame1;
		if (frame1.empty()) break;

		cv::pyrDown(frame1, frame2);
		cv::imshow("frame 1", frame1);
		cv::imshow("frame 2", frame2);
		writer << frame2;

		char ch = cv::waitKey(1000 / 30);
		if (ch == 'q') break;
	}
	cv::destroyWindow("frame 1");
	cv::destroyWindow("frame 2");
	return 0;
}