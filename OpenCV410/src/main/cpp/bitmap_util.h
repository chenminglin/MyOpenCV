#include <jni.h>
#include <opencv2/core/mat.hpp>
#include <android/bitmap.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/photo.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Contrast.h"

extern "C" {
JNIEXPORT jobject JNICALL Java_com_bethena_opencv410_BitmapUtil_blackAnWhiteFilter(JNIEnv *env, jobject thiz, jobject srcBitmap);
JNIEXPORT jobject JNICALL Java_com_bethena_opencv410_BitmapUtil_maggicFilter(JNIEnv *env, jobject thiz, jobject srcBitmap);
JNIEXPORT jobjectArray JNICALL Java_com_bethena_opencv410_BitmapUtil_cropToPoints(JNIEnv *env, jobject thiz, jobject inputBitmap);
}
