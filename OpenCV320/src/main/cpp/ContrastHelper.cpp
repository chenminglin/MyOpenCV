// ContrastHelper.cpp
#include "ContrastHelper.h"

double ContrastHelper::getContrastValue(int n) {
    switch (n) {
        case 1: return VERY_DARK_IMAGE;
        case 2: return DARK_IMAGE;
        case 3: return NORMAL_IMAGE;
        case 4: return BRIGHT_IMAGE;
        case 5: return VERY_BRIGHT_IMAGE;
        default: return NORMAL_IMAGE;
    }
}
