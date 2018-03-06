package com.lj.jnisnippet;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("native-lib");
    }

    // java get/set
    private native String getNative();
    private native void setNative(int num, String str);

    // native get/set
    private native void testSetJava();
    private native void testGetJava();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        log("getNative:" + getNative());
        setNative(17, "joaquin");
        testSetJava();
        testGetJava();
    }

    private void setJava(int num, String str) {
        log("setJava num:" + num + ", str:" + str);
    }

    private String getJava() {
        log("getJava");
        return "Hello from Java";
    }

    private static void log(String msg) {
        Log.d("[java]", msg);
    }

}
