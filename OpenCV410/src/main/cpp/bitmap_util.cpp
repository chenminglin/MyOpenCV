#include <iostream>
#include "bitmap_util.h"


using namespace cv;
using namespace std;

// Helper function to convert a jobject to a cv::Mat
Mat jobjectToMat(JNIEnv *env, jobject bitmap) {
    AndroidBitmapInfo info;
    void *pixels;
    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        // Handle error
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        // Handle error
    }

    Mat mat(info.height, info.width, CV_8UC4, pixels);
    AndroidBitmap_unlockPixels(env, bitmap);

    return mat;
}

jobject createBitmap(JNIEnv *env, int width, int height, int format) {
    jclass bitmap_class = env->FindClass("android/graphics/Bitmap");
    jmethodID create_bitmap_method = env->GetStaticMethodID(bitmap_class, "createBitmap",
                                                            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jclass config_class = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID config_field;
    if (format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        config_field = env->GetStaticFieldID(config_class, "ARGB_8888",
                                             "Landroid/graphics/Bitmap$Config;");
    } else {
        config_field = env->GetStaticFieldID(config_class, "RGB_565",
                                             "Landroid/graphics/Bitmap$Config;");
    }
    jobject config = env->GetStaticObjectField(config_class, config_field);

    jobject bitmap = env->CallStaticObjectMethod(bitmap_class, create_bitmap_method, width, height,
                                                 config);

    return bitmap;
}

// Helper function to convert a cv::Mat to a jobject
jobject matToJobject(JNIEnv *env, const Mat &mat) {
    if (!mat.isContinuous()) {
        return NULL;
    }

    int width = mat.cols;
    int height = mat.rows;
    int channels = mat.channels();

    // Create an empty Bitmap with the correct width, height, and format
    jobject bitmap = createBitmap(env, width, height, ANDROID_BITMAP_FORMAT_RGBA_8888);

    // Lock the pixels of the Bitmap
    void *bitmapPixels;
    AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels);

    // Copy the Mat data to the Bitmap
    if (channels == 1) {
        Mat temp(height, width, CV_8UC4, bitmapPixels);
        cvtColor(mat, temp, COLOR_GRAY2RGBA);
    } else {
        Mat temp(height, width, CV_8UC4, bitmapPixels);
        cvtColor(mat, temp, COLOR_BGR2RGBA);
    }

    // Unlock the pixels of the Bitmap
    AndroidBitmap_unlockPixels(env, bitmap);

    return bitmap;
}


extern "C" JNIEXPORT jobject JNICALL
Java_com_bethena_opencv410_BitmapUtil_blackAnWhiteFilter(JNIEnv *env, jobject thiz,
                                                         jobject srcBitmap) {
    AndroidBitmapInfo srcBitmapInfo;
    void *srcBitmap_pixels;
    int srcBitmap_width, srcBitmap_height;

    AndroidBitmap_getInfo(env, srcBitmap, &srcBitmapInfo);
    srcBitmap_width = srcBitmapInfo.width;
    srcBitmap_height = srcBitmapInfo.height;

    // Get the number of channels from the original bitmap
    int channels = (srcBitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) ? 4 : 3;

    // Convert input Bitmap to Mat with the correct number of channels
    Mat mat(srcBitmap_width, srcBitmap_height, CV_8UC(channels));
    AndroidBitmap_lockPixels(env, srcBitmap, &srcBitmap_pixels);
    Mat temp(srcBitmap_height, srcBitmap_width, CV_8UC4, srcBitmap_pixels);
    temp.copyTo(mat);
    AndroidBitmap_unlockPixels(env, srcBitmap);

    cvtColor(mat, mat, COLOR_RGBA2BGR);
    cvtColor(mat, mat, COLOR_BGR2GRAY);
    jobject result = matToJobject(env, mat);
    mat.release();

    return result;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_bethena_opencv410_BitmapUtil_maggicFilter(JNIEnv *env, jobject thiz, jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    void *pixels;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    Mat srcArry(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
    double contrast_value = Contrast::getContrastLevel(srcArry);

    if (srcArry.channels() >= 3) {
        Mat channel;
        cvtColor(srcArry, srcArry, COLOR_BGR2HSV);

        extractChannel(srcArry, channel, 2);
        Ptr<CLAHE> clahe = createCLAHE();
        clahe->setClipLimit(1.0);
        clahe->apply(channel, channel);
        insertChannel(channel, srcArry, 2);

        extractChannel(srcArry, channel, 1);
        Ptr<CLAHE> clahe2 = createCLAHE();
        clahe2->setClipLimit(1.0);
        clahe2->apply(channel, channel);
        insertChannel(channel, srcArry, 1);

        cvtColor(srcArry, srcArry, COLOR_HSV2BGR);
        channel.release();
    }
    // Create a new Mat object with the same size as srcArry
    Mat resultMat;
    srcArry.convertTo(resultMat, -1, contrast_value, 29.0);
    AndroidBitmap_unlockPixels(env, bitmap);

    return matToJobject(env, resultMat);
}


vector<Point> sortPoints(vector<Point> unorderedPoints) {
    Point topLeft = *min_element(unorderedPoints.begin(), unorderedPoints.end(),
                                 [](const Point &a, const Point &b) {
                                     return (a.x + a.y) < (b.x + b.y);
                                 });
    Point bottomRight = *max_element(unorderedPoints.begin(), unorderedPoints.end(),
                                     [](const Point &a, const Point &b) {
                                         return (a.x + a.y) < (b.x + b.y);
                                     });

    vector<Point> others;
    for (const auto &point: unorderedPoints) {
        if (point != topLeft && point != bottomRight) {
            others.push_back(point);
        }
    }
    Point topRight = *max_element(others.begin(), others.end(),
                                  [](const Point &a, const Point &b) {
                                      return (a.x - a.y) < (b.x - b.y);
                                  });
    Point bottomLeft = *min_element(others.begin(), others.end(),
                                    [](const Point &a, const Point &b) {
                                        return (a.x - a.y) < (b.x - b.y);
                                    });

    return vector<Point>{topLeft, topRight, bottomRight, bottomLeft};
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_bethena_opencv410_BitmapUtil_cropToPoints(JNIEnv *env, jobject thiz, jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    void *pixels;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    Mat image(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
    vector<Point> quadPoints;
    try {
        Mat gray(image.rows, image.cols, CV_8UC1);
        cvtColor(image, gray, COLOR_BGR2GRAY);
        threshold(gray, gray, 150.0, 255.0, THRESH_BINARY + THRESH_OTSU);

        vector<vector<Point>> contours;
        Mat hierarchy;
        findContours(gray, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

        sort(contours.begin(), contours.end(), [](const vector<Point> &a, const vector<Point> &b) {
            return contourArea(a) > contourArea(b);
        });

        vector<Point2f> contour2f(contours[0].begin(), contours[0].end());
        double epsilon = 0.02 * arcLength(contour2f, true);
        vector<Point2f> approx;
        approxPolyDP(contour2f, approx, epsilon, true);

        if (approx.size() == 4) {
            vector<Point> unorderedPoints(approx.begin(), approx.end());
            quadPoints = sortPoints(unorderedPoints);
        }
    } catch (const exception &e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    jobjectArray resultPoints = env->NewObjectArray(4, env->FindClass("android/graphics/Point"),
                                                    nullptr);

    for (size_t i = 0; i < quadPoints.size(); i++) {
        jclass pointClass = env->FindClass("android/graphics/Point");
        jmethodID pointConstructor = env->GetMethodID(pointClass, "<init>", "(II)V");
        jobject point = env->NewObject(pointClass, pointConstructor, quadPoints[i].x,
                                       quadPoints[i].y);
        env->SetObjectArrayElement(resultPoints, i, point);
        env->DeleteLocalRef(point);
    }

    AndroidBitmap_unlockPixels(env, bitmap);
    return resultPoints;
}