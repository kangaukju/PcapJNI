package com.example.kinow.testdemo;

/**
 * Created by kinow on 15. 12. 25.
 */
public class HlloNDK {
    static {
        System.loadLibrary("hello");
    }
    public native String getHello();
}
