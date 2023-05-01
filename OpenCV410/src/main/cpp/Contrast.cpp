// Contrast.cpp
#include "Contrast.h"

double Contrast::getContrastLevel(const cv::Mat& src) {
    float range[] = {0, 256};
    const float* ranges[] = {range};
    int brightnessVal[5] = {0};
    int sum = 0;
    int max = std::numeric_limits<int>::min();
    int ans = -1;

    cv::Mat valueHist;

    cv::Mat srcArray = src.clone();

    if (srcArray.channels() >= 3) {
        cv::cvtColor(srcArray, srcArray, cv::COLOR_BGR2HSV);
        srcArray.convertTo(srcArray, CV_8U); // 添加这一行代码以将srcArray转换为8位无符号整数格式

        std::vector<cv::Mat> bgrPlanes;
        cv::split(srcArray, bgrPlanes);

        int histSize = 256;
        int channels[] = {0};
        cv::calcHist(&bgrPlanes[2], 1, channels, cv::Mat(), valueHist, 1, &histSize, ranges, true, false);


        float bHistData[256];
        cv::Mat bHistDataMat(1, 256, CV_32F, bHistData);
        valueHist.copyTo(bHistDataMat);


        for (int i = 1; i < 256; ++i) {
            int p = static_cast<int>(std::round(bHistData[i]));
            int divideBy = 51;

            if (i < 52) {
                sum += p;
                if (i == 51) {
                    brightnessVal[0] = sum / divideBy;
                    sum = 0;
                }
            } else if (i < 103) {
                sum += p;
                if (i == 102) {
                    brightnessVal[1] = sum / divideBy;
                    sum = 0;
                }
            } else if (i < 154) {
                sum += p;
                if (i == 153) {
                    brightnessVal[2] = sum / divideBy;
                    sum = 0;
                }
            } else if (i < 204) {
                sum += p;
                if (i == 203) {
                    brightnessVal[3] = sum / divideBy;
                    sum = 0;
                }
            } else {
                sum += p;
                if (i == 255) {
                    brightnessVal[4] = sum / divideBy;
                    sum = 0;
                }
            }
        }

        for (int i = 0; i < 5; ++i) {
            if (max < brightnessVal[i]) {
                max = brightnessVal[i];
                ans = i;
            }
        }
    }
    return ContrastHelper::getContrastValue(ans);
}
