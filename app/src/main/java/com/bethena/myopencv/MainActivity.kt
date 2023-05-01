package com.bethena.myopencv

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.bethena.myopencv.databinding.ActivityMainBinding
import com.bethena.opencv410.BitmapUtil
import com.bethena.opencv410.NativeLib
//import com.bethena.opencv320.NativeLib

class MainActivity : AppCompatActivity() {

//    init {
//        System.loadLibrary("opencv_java4")
//    }

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        NativeLib()
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
//        Loader.load(Core.NATIVE_LIBRARY_NAME);

        // Example of a call to a native method
        ImageLoader.getBitmapFromAsset(this, "img_1.png")?.let {
//            var outBitmap = NativeLib().convertToGray(it)
//            binding.ivImage.setImageBitmap(BitmapUtil.blackAnWhiteFilter(it))
            binding.ivImage.setImageBitmap(BitmapUtil.maggicFilter(it))
            BitmapUtil.cropToPoints(it).forEach {
                println("point: $it")
            }
        }

    }

    override fun onResume() {
        super.onResume()
//        OpenCVLoader.initDebug()
    }


}