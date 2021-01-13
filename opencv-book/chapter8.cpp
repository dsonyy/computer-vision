#include "exercises.h"

int grab_retrieve_camera() {
	std::chrono::steady_clock::time_point t0, t1, t2;
	cv::VideoCapture cam0(0), cam1(1);
	cv::Mat img0, img1;
	bool ok0 = 1, ok1 = 1;

	cv::namedWindow("0");
	cv::namedWindow("1");

	while (true) {
		t0 = std::chrono::steady_clock::now();
		ok0 = cam1.grab();
		t1 = std::chrono::steady_clock::now();
		ok1 = cam0.grab();
		t2 = std::chrono::steady_clock::now();

		std::cout << "0 CAMERA TIME: "
			<< std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << "us\n"
			<< "1 CAMERA TIME: "
			<< std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "us\n";

		CV_Assert(ok0 == true);
		CV_Assert(ok1 == true);

		ok0 = cam0.retrieve(img0);
		ok1 = cam1.retrieve(img1);

		CV_Assert(ok0 == true);
		CV_Assert(ok1 == true);

		cv::imshow("0", img0);
		cv::imshow("1", img1);
		if ('q' == cv::waitKey(0)) break;
	}

	return 0;
}

void mouse_callback(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
		case cv::EVENT_MOUSEMOVE:
			break;
		case cv::EVENT_LBUTTONDOWN:
		case cv::EVENT_RBUTTONDOWN:
		case cv::EVENT_MBUTTONDOWN:
		case cv::EVENT_LBUTTONUP:
		case cv::EVENT_RBUTTONUP:
		case cv::EVENT_MBUTTONUP:
		case cv::EVENT_LBUTTONDBLCLK:
		case cv::EVENT_RBUTTONDBLCLK:
		case cv::EVENT_MBUTTONDBLCLK:
		case cv::EVENT_MOUSEWHEEL:
		case cv::EVENT_MOUSEHWHEEL:
			cv::Mat* mat = (cv::Mat*)userdata;
			std::cout << x << " " << y << "\t" << mat->at<cv::Vec3b>(x, y) << std::endl;
	}
}

int mouse_click() {
	cv::Mat mat = cv::imread("../res/lena.bmp");

	cv::namedWindow("lena");
	cv::setMouseCallback("lena", mouse_callback, &mat);

	cv::imshow("lena", mat);
	while (true) {
		if ('q' == cv::waitKey(10)) break;
	}

	return 0;
}

struct selection {
	cv::Point p0;
	cv::Point p1;
	bool hold = false;
	bool update = false;
};

void mouse_callback2(int event, int x, int y, int flags, void* userdata) {
	selection* sel = (selection*)userdata;
	if (event == cv::EVENT_LBUTTONDOWN) {
		sel->hold = true;
		sel->p0.x = x;
		sel->p0.y = y;
		sel->p1.x = x;
		sel->p1.y = y;
		sel->update = true;
	}
	else if (sel->hold && event == cv::EVENT_MOUSEMOVE) {
		sel->p1.x = x;
		sel->p1.y = y;
		sel->update = true;
	}
	else if (event == cv::EVENT_LBUTTONUP) {
		sel->hold = false;
		sel->update = true;
	}
}

int mouse_select() {
	cv::Mat mat = cv::imread("../res/lena.bmp");
	selection sel;

	cv::namedWindow("lena");
	cv::setMouseCallback("lena", mouse_callback2, &sel);

	cv::Mat mat2 = mat.clone();
	while (true) {
		if (sel.update) {
			mat2 = mat.clone();
			if (sel.hold)
				cv::rectangle(mat2, sel.p0, sel.p1, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
			else 
				cv::rectangle(mat2, sel.p0, sel.p1, cv::Scalar(255, 255, 255), cv::FILLED, cv::LINE_8);
		}

		std::cout << sel.p0.x << " " << sel.p0.y << " " 
			<< sel.p1.x << " " << sel.p1.y << std::endl;

		cv::imshow("lena", mat2);
		if ('q' == cv::waitKey(10)) break;
	}

	return 0;
}