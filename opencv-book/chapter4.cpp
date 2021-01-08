#include "exercises.h"

void draw_number(cv::Mat_<cv::Vec3b>& img, const cv::Point2i& p, char ch, const cv::Scalar& c) {
	std::array<bool, 7> sgmts;
	/*
	   ===3===
	  |       |
	  1       6
      |       |
	   ===4===
	  |       |
	  2       7
      |       |
	   ===5===
	*/
	//                            1  2  3  4  5  6  7
	if (ch == '0')      sgmts = { 1, 1, 1, 0, 1, 1, 1 };
	else if (ch == '1') sgmts = { 0, 0, 0, 0, 0, 1, 1 };
	else if (ch == '2') sgmts = { 0, 1, 1, 1, 1, 1, 0 };
	else if (ch == '3') sgmts = { 0, 0, 1, 1, 1, 1, 1 };
	else if (ch == '4') sgmts = { 1, 0, 0, 1, 0, 1, 1 };
	else if (ch == '5') sgmts = { 1, 0, 1, 1, 1, 0, 1 };
	else if (ch == '6') sgmts = { 1, 1, 1, 1, 1, 0, 1 };
	else if (ch == '7') sgmts = { 0, 0, 1, 0, 0, 1, 1 };
	else if (ch == '8') sgmts = { 1, 1, 1, 1, 1, 1, 1 };
	else if (ch == '9') sgmts = { 1, 0, 1, 1, 1, 1, 1 };

	if (sgmts[0]) { auto m = img(cv::Range(p.y + 1, p.y + 10), cv::Range(p.x + 1, p.x + 2)); m.setTo(c); } // 1
	if (sgmts[1]) { auto m = img(cv::Range(p.y + 10, p.y + 20), cv::Range(p.x + 1, p.x + 2)); m.setTo(c); } // 2
	if (sgmts[2]) { auto m = img(cv::Range(p.y + 1, p.y + 2), cv::Range(p.x + 1, p.x + 10)); m.setTo(c); } // 3
	if (sgmts[3]) { auto m = img(cv::Range(p.y + 9, p.y + 10), cv::Range(p.x + 1, p.x + 10)); m.setTo(c); } // 4
	if (sgmts[4]) { auto m = img(cv::Range(p.y + 19, p.y + 20), cv::Range(p.x + 1, p.x + 10)); m.setTo(c); } // 5
	if (sgmts[5]) { auto m = img(cv::Range(p.y + 1, p.y + 10), cv::Range(p.x + 9, p.x + 10)); m.setTo(c); } // 6 
	if (sgmts[6]) { auto m = img(cv::Range(p.y + 10, p.y + 20), cv::Range(p.x + 9, p.x + 10)); m.setTo(c); } // 7

}

int numerical_keyboard() {
	auto sz = cv::Size(500, 500);
	cv::Mat_<cv::Vec3b> img = cv::Mat_<cv::Vec3b>::zeros(sz);
	auto chsz = cv::Size(10, 20);
	auto pos = cv::Point();
	auto c = cv::Scalar();

	cv::namedWindow("numkey", cv::WINDOW_AUTOSIZE);
	while (true) {
		auto cur = img(cv::Rect(pos, chsz));
		cur = ~cur;
		cv::imshow("numkey", img);
		cur = ~cur;
		
		cv::randu(c, cv::Scalar(100), cv::Scalar(256));
		auto ch = cv::waitKey(0);
		if (ch == 'q') break;
		else if (ch >= '0' && ch <= '9') {
			draw_number(img, pos, ch, c);
			if (sz.width - chsz.width > pos.x) pos.x += chsz.width;
			else if (sz.height - chsz.height > pos.y) pos = cv::Point(0, pos.y + chsz.height);
		}
		else if (ch == 'e' && sz.height - chsz.height > pos.y) pos = cv::Point(0, pos.y + chsz.height);
		else if (ch == 'a' && 0 < pos.x) pos.x -= chsz.width;
		else if ((ch == 'd' || ch == ' ') && sz.width - chsz.width  > pos.x) pos.x += chsz.width;
		else if (ch == 'w' && 0 < pos.y) pos.y -= chsz.height;
		else if (ch == 's' && sz.height - chsz.height > pos.y) pos.y += chsz.height;
	}

	return 0;
}

int summed_area_table() {
	cv::Size sz(500, 500);
	cv::Mat mat(sz, CV_32FC1);
}