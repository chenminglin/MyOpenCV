package com.bethena.opencv320

import android.graphics.Bitmap

class NativeLib {

    /**
     * A native method that is implemented by the 'opencv320' native library,
     * which is packaged with this application.
     */
    external fun convertToGray(inputBitmap: Bitmap): Bitmap

    companion object {
        // Used to load the 'opencv320' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}