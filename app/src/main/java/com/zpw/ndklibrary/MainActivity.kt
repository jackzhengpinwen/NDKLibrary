package com.zpw.ndklibrary

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.SystemClock
import android.util.Log
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

        val dog = Animal("dog")
        accessInstanceFiled(dog)
        Log.d(TAG, "dog name is changed ${dog.name}")

        accessStaticField(dog)
        Log.d(TAG, "dog num is changed ${dog.num}")

        callInstanceMethod(dog)

        callStaticMethod(dog)

        Log.d(TAG, "invokeStringConstructors is " + invokeStringConstructors())

        val animal = allocObjectConstructor()
        Log.d(TAG, "allocObjectConstructor is ${animal.name}")

        callSuperMethod()

        for (i in 0 until 10) {
//            SystemClock.sleep(500)
            staticCacheField(Animal("dog"))
        }

        for (i in 0 until 10) {
            SystemClock.sleep(500)
            callCacheMethod(Animal("dog"))
        }

        for (i in 0 until 10) {
            SystemClock.sleep(500)
            useWeakGlobalReference()
        }

        exceptionDealer()

        try {
            nativeThrowException()
        } catch (e : IllegalArgumentException) {
            Log.d(TAG, "nativeThrowException  ${e.message}")
        }

        createNativeThread()
    }

    external fun createNativeThread()

    external fun nativeThrowException()

    external fun exceptionDealer()

    external fun useWeakGlobalReference()

    external fun cacheWithGlobalReference(): String

    external fun errorCacheUseLocalReference(): String

    external fun callCacheMethod(animal: Animal)

    external fun staticCacheField(animal: Animal)

    external fun callSuperMethod()

    external fun allocObjectConstructor(): Animal

    external fun invokeStringConstructors(): String

    external fun getNativeString(s: String): String

    external fun getNativeArray(array: IntArray, num: Int): Int

    external fun getIntArray(num: Int): IntArray

    external fun getTwoDimensionalArray(size: Int): Array<IntArray>

    external fun printAnimalsName(animal: Array<Animal>)

    external fun accessInstanceFiled(animal: Animal)

    external fun accessStaticField(animal: Animal)

    external fun callInstanceMethod(animal: Animal)

    external fun callStaticMethod(animal: Animal)

    companion object {
        // Used to load the 'ndklibrary' library on application startup.
        init {
            System.loadLibrary("ndklibrary")
        }
    }
}