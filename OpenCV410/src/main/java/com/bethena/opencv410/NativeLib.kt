package com.bethena.opencv410

import android.graphics.Bitmap
import android.util.Log

class NativeLib {

    external fun convertToGray(inputBitmap: Bitmap): Bitmap

    companion object {
        // Used to load the 'opencv320' library on application startup.
        init {
//            System.loadLibrary("opencv_core")
//            System.loadLibrary("opencv_imgproc")
            System.loadLibrary("cvtool")


            Log.d("NativeLib","load so success")
        }
    }
}