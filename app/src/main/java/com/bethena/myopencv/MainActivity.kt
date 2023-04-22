package com.bethena.myopencv

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.bethena.myopencv.databinding.ActivityMainBinding
import com.bethena.opencv320.NativeLib

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "111111"
        NativeLib().convertToGray("/sdcard/DCIM/OpenCamera/IMG_20221206_090734.jpg", "/sdcard/DCIM/OpenCamera/IMG_20221206_090734_2.jpg")
    }


}