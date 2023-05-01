// ContrastHelper.h
#pragma once

class ContrastHelper {
public:
    static constexpr double VERY_DARK_IMAGE = 1.5;
    static constexpr double DARK_IMAGE = 1.4;
    static constexpr double NORMAL_IMAGE = 1.3;
    static constexpr double BRIGHT_IMAGE = 1.25;
    static constexpr double VERY_BRIGHT_IMAGE = 1.2;

    static double getContrastValue(int n);
};

