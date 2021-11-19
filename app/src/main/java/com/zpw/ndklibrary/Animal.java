package com.zpw.ndklibrary;

import android.util.Log;

public class Animal {
    private static final String TAG = "Animal";

    static {
        init(); // 静态代码块中进行缓存
    }

    private static native void init();

    protected String name;
    public static int num = 0;

    public Animal() {}

    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public int getNum() {
        return num;
    }

    public void callInstanceMethod(int i) {
        Log.d(TAG, "callInstanceMethod i is " + i);
    }

    public static String callStaticMethod(String s) {
        Log.d(TAG, "callStaticMethod s is " + s);
        return s;
    }

    private int exceptionFun() {
        return 2 / 0;
    }
}
