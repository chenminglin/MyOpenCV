// Contrast.h
#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "ContrastHelper.h"

class Contrast {
public:
    static double getContrastLevel(const cv::Mat& src);
};
