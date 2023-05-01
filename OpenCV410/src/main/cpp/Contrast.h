// Contrast.h
#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "ContrastHelper.h"

class Contrast {
public:
    static double getContrastLevel(const cv::Mat& src);
};
