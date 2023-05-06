package com.nytrostudios.mycalculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.nytrostudios.mycalculator.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        val equal = findViewById<Button>(R.id.Equals)
        val op = "1+1"


        equal.setOnClickListener {
            binding.sampleText.text = calc(op)

        }
    }

    /**
     * A native method that is implemented by the 'mycalculator' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun calc(string: String): String

    companion object {
        // Used to load the 'mycalculator' library on application startup.
        init {
            System.loadLibrary("mycalculator")
        }
    }
}