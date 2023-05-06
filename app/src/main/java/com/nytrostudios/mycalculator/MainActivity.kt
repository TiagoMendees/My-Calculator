package com.nytrostudios.mycalculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.nytrostudios.mycalculator.databinding.ActivityMainBinding

fun concat(s1: String, s2: String): String {
    return s1 + s2
}

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val equal = findViewById<Button>(R.id.Equals)
        val zero = findViewById<Button>(R.id.zero)
        val one = findViewById<Button>(R.id.one)
        val two = findViewById<Button>(R.id.two)
        val three = findViewById<Button>(R.id.three)
        val four = findViewById<Button>(R.id.four)
        val five = findViewById<Button>(R.id.five)
        val six = findViewById<Button>(R.id.six)
        val seven = findViewById<Button>(R.id.seven)
        val eight = findViewById<Button>(R.id.eight)
        val nine = findViewById<Button>(R.id.nine)
        val plus = findViewById<Button>(R.id.Plus)
        val divide = findViewById<Button>(R.id.divide)
        val minus = findViewById<Button>(R.id.minus)
        val multiply = findViewById<Button>(R.id.Multiply)
        val clear = findViewById<Button>(R.id.Clear)
        var op = "1+1"


        equal.setOnClickListener {
            binding.sampleText2.text = calc(op)

        }

        clear.setOnClickListener {op = ""; binding.sampleText.text = ""; binding.sampleText2.text = ""}
        plus.setOnClickListener { op = concat(op, "+"); binding.sampleText.text = op}
        divide.setOnClickListener { op = concat(op, "/"); binding.sampleText.text = op }
        multiply.setOnClickListener { op = concat(op, "*"); binding.sampleText.text = op }
        minus.setOnClickListener { op = concat(op, "-"); binding.sampleText.text = op }
        one.setOnClickListener { op = concat(op, "1"); binding.sampleText.text = op }
        two.setOnClickListener { op = concat(op, "2"); binding.sampleText.text = op }
        three.setOnClickListener { op = concat(op, "3"); binding.sampleText.text = op }
        four.setOnClickListener { op = concat(op, "4"); binding.sampleText.text = op }
        five.setOnClickListener { op = concat(op, "5"); binding.sampleText.text = op }
        six.setOnClickListener { op = concat(op, "6"); binding.sampleText.text = op }
        seven.setOnClickListener { op = concat(op, "7"); binding.sampleText.text = op }
        eight.setOnClickListener { op = concat(op, "8"); binding.sampleText.text = op }
        nine.setOnClickListener { op = concat(op, "9"); binding.sampleText.text = op }
        zero.setOnClickListener { op = concat(op, "0"); binding.sampleText.text = op }
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