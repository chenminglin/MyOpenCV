#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <android/log.h>
#include <jni.h>

using namespace cv;
using namespace std;

extern "C" {

JNIEXPORT void JNICALL
Java_com_bethena_opencv320_NativeLib_convertToGray(JNIEnv *env, jobject instance,
                                                    jstring inputImagePath, jstring outputImagePath) {

    const char *inputImagePathCStr = env->GetStringUTFChars(inputImagePath, 0);
    const char *outputImagePathCStr = env->GetStringUTFChars(outputImagePath, 0);

    Mat src, gray;

    // Read the image
    src = imread(inputImagePathCStr, IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (src.empty()) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenCV", "Cannot read image %s", inputImagePathCStr);
        return;
    }

    // Convert the image to grayscale
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Save the grayscale image
    imwrite(outputImagePathCStr, gray);

    // Release resources
    env->ReleaseStringUTFChars(inputImagePath, inputImagePathCStr);
    env->ReleaseStringUTFChars(outputImagePath, outputImagePathCStr);
}

} // extern "C"

