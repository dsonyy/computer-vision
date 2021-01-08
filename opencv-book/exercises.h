#include <opencv2/opencv.hpp>
#include <functional>
#pragma once

// Chapter 1

// Chapter 2
int load_image();
int load_video();
int load_video_slider();
int read_camera();
int save_video();
int read_save_camera();


// Chapter 3
int chapter3();

// Chapter 4


// Specify function which will be run by main().
#define RUN_FN read_save_camera
