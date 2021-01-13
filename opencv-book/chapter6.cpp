#include "exercises.h"

int shapes() {
	cv::Mat_<cv::Vec3b> mat = cv::imread("../res/lena.bmp");

	cv::circle(mat, 
		cv::Point(mat.cols, mat.rows) / 2, 
		100, 
		{ 0, 255, 0}, 
		cv::FILLED, 
		cv::LINE_AA
	);

	cv::ellipse(mat,
		cv::Point(100, 100),
		cv::Size(100, 50),
		45,
		0,
		360,
		{ 255, 0, 255 },
		5,
		cv::LINE_AA
	);

	cv::Point pts[] = { 
		cv::Point(-10, -10), cv::Point(100, 50), cv::Point(-40, 100), 
	};
	cv::fillConvexPoly(mat, pts, 3, { 255, 0, 0 });
	// Note: Using cv::FILLED raises an exception

	std::vector<std::vector<cv::Point>> vpts = {
		{ cv::Point(-10, -10), cv::Point(100, 50), cv::Point(300, 30), },
	};
	cv::fillPoly(mat, vpts,	{ 0, 0, 255 });

	cv::line(mat, cv::Point(300, 500), cv::Point(700, 400), { 255, 255, 0 }, 10, cv::LINE_8);
	cv::line(mat, cv::Point(300, 400), cv::Point(700, 300), { 255, 0, 255 }, 10, cv::LINE_4);
	cv::line(mat, cv::Point(300, 300), cv::Point(700, 200), { 255, 0, 255 }, 10, cv::LINE_AA);

	cv::rectangle(mat, cv::Rect(400, 300, 500, 400), 0, 5, cv::LINE_AA);

	cv::LineIterator lit(mat, cv::Point(100, 100), cv::Point(200, 80));
	for (int i = 0; i < lit.count; i++, lit++) {
		auto pos = lit.pos();
		auto pt = *(cv::Vec3b*)*lit;
		std::cout << pos.x << ", " << pos.y << ": " 
			<< int(pt[0]) << " " << int(pt[1]) << " " << int(pt[2]) << std::endl;
	}

	cv::namedWindow("win", cv::WINDOW_AUTOSIZE);
	cv::imshow("win", mat);
	cv::waitKey();

	return 0;
}

std::string type2str(int type) {
	// Source: https://stackoverflow.com/a/17820615/7389107
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

int grayscale_with_text() {
	cv::Mat mat = cv::imread("../res/lena.bmp");
	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
	cv::cvtColor(mat, mat, cv::COLOR_GRAY2BGR);
	std::cout << CV_MAT_CN(mat.type()) << std::endl;
	for (int i = 0; i < 8; i++) {
		cv::putText(
			mat,
			"Szymon Bednorz",
			cv::Point(100, 100 + 40 * i),
			i,
			1,
			cv::Scalar(),
			2,
			cv::LINE_AA
		);
		cv::putText(
			mat,
			"Szymon Bednorz",
			cv::Point(96, 96 + 40 * i),
			i,
			1,
			cv::Scalar(0, 255, 255),
			2,
			cv::LINE_AA
		);
	}

	cv::namedWindow("win", cv::WINDOW_AUTOSIZE);
	cv::imshow("win", mat);
	cv::waitKey();
	return 0;
}

int fps() {
	cv::VideoCapture cap("../res/video.mp4");
	cv::namedWindow("win", cv::WINDOW_AUTOSIZE);

	cv::Mat frame;
	float fps = 0;
	std::chrono::steady_clock::time_point end, begin 
		= std::chrono::steady_clock::now();

	while (true) {
		cap.read(frame);

		cv::putText(
			frame,
			std::to_string(fps) + " fps",
			cv::Point(10, 20),
			cv::FONT_HERSHEY_PLAIN,
			1,
			cv::Scalar::all(255),
			1,
			cv::LINE_AA
		);

		cv::imshow("win", frame);
		end = std::chrono::steady_clock::now();
		fps = 1000.0f / std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		begin = std::chrono::steady_clock::now();
		char ch = cv::waitKey(1000 / 30);
		if (ch == 'q') break;
	}

	return 0;
}
