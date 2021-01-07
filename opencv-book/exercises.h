#include <opencv2/opencv.hpp>
#include <functional>
#pragma once

// CH 1

// CH 2
int load_image();
int load_video();
int load_video_slider();

// Specify function which will be run by main().
#define RUN_FN load_video_slider
