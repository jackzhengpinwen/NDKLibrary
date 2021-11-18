package com.zpw.ndklibrary

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.zpw.ndklibrary.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private val TAG = "MainActivity"

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = getNativeString("hello java string")
        val nativeArray = getNativeArray(intArrayOf(1, 2, 3), 2)
        Log.d(TAG, "nativeArray is: $nativeArray")

        val intArray: IntArray = getIntArray(3)
        intArray.forEach {
            Log.d(TAG, "intArray is $it")
        }

        val twoDimensionalArray: Array<IntArray> = getTwoDimensionalArray(2)
        twoDimensionalArray.forEach { array ->
            array.forEach {
                Log.d(TAG, "twoDimensionalArray is $it")
            }
        }

        printAnimalsName(arrayOf(Animal("bird"), Animal("cat")))
    }

    external fun getNativeString(s: String): String

    external fun getNativeArray(array: IntArray, num: Int): Int

    external fun getIntArray(num: Int): IntArray

    external fun getTwoDimensionalArray(size: Int): Array<IntArray>

    external fun printAnimalsName(animal: Array<Animal>)


    companion object {
        // Used to load the 'ndklibrary' library on application startup.
        init {
            System.loadLibrary("ndklibrary")
        }
    }
}

open class Animal {
    lateinit var name: String

    constructor(name: String) {
        this.name = name
    }
}