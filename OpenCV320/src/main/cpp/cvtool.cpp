#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <android/log.h>
#include <android/bitmap.h>
#include <jni.h>

using namespace cv;
using namespace std;

extern "C" {

JNIEXPORT jobject JNICALL
Java_com_bethena_opencv320_NativeLib_convertToGray(JNIEnv *env, jobject instance, jobject bitmap) {

    // Convert the input Bitmap to OpenCV Mat
    AndroidBitmapInfo input_info;
    void *input_pixels;
    AndroidBitmap_getInfo(env, bitmap, &input_info);
    AndroidBitmap_lockPixels(env, bitmap, &input_pixels);

    cv::Mat input_image(input_info.height, input_info.width, CV_8UC4, input_pixels);
    cv::cvtColor(input_image, input_image, cv::COLOR_BGRA2BGR);

    // Convert the input image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);

    // Convert the grayscale image back to BGRA format
    cv::cvtColor(gray_image, gray_image, cv::COLOR_GRAY2BGRA);

    // Create an empty Bitmap for the output image
    jobject output_bitmap = env->NewGlobalRef(bitmap);

    // Set the output Bitmap's pixels to the grayscale image
    AndroidBitmap_unlockPixels(env, bitmap);
    AndroidBitmap_lockPixels(env, output_bitmap, &input_pixels);
    memcpy(input_pixels, gray_image.data, gray_image.total() * gray_image.elemSize());
    AndroidBitmap_unlockPixels(env, output_bitmap);

    return output_bitmap;
}

} // extern "C"

