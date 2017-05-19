package com.example.javatonative;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;


public class MainActivity extends Activity {
    private static final String TAG = "MainActivity";
    //定义一个需要排序的数组
    private int[] mArray = {8,2,9,6,10,7,20,37,13,15};
    static {
        System.loadLibrary("JavaToNative");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.e(TAG, "*******************before sort*************");
        printArray(mArray);
        heapSortNative(mArray);
        Log.e(TAG, "*******************after sort*************");
        printArray(mArray);
        Log.e(TAG, "*******************reverse array*************");
        reverseArrayNative(mArray);
        printArray(mArray);
    }

    private void printArray(int[] array){
        for (int i = 0; i < array.length; i++){
            Log.e(TAG,"array[" + i + "]: " + array[i]);
        }
    }

    /**
     * 堆排序，调用本地方法完成排序，并将排序后的结果通过array返回
     * @param array 待排序的数组
     */
    private native void heapSortNative(int[] array);

    /**
     * 翻转数组
     * @param array 待翻转的数组
     */
    private native void reverseArrayNative(int[] array);
}
