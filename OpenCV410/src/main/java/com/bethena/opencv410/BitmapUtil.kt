package com.bethena.opencv410

import android.graphics.Bitmap

object BitmapUtil {
    external fun blackAnWhiteFilter(bitmap: Bitmap): Bitmap

    external fun maggicFilter(bitmap: Bitmap): Bitmap

    external fun cropToPoints(bitmap: Bitmap): Array<android.graphics.Point>
}