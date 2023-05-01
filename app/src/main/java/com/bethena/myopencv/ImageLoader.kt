package com.bethena.myopencv

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory

import java.io.IOException

object ImageLoader {
    fun getBitmapFromAsset(context: Context, strName: String): Bitmap? {
        val assetManager = context.assets
        return try {
            val istr = assetManager.open(strName)
            BitmapFactory.decodeStream(istr)
        } catch (e: IOException) {
            e.printStackTrace()
            null
        }
    }


}