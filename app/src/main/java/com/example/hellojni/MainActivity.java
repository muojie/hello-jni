package com.example.hellojni;

/**
 * Created by lenovo on 2017/11/30.
 */

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        init();
    }

    public String name = "test";
    private int[] source = {1,4,0,7,33,11};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        //tv.setText(getMethod());
        //数组的访问
        getArray(source);
        for (int i=0;i<source.length;i++){
            Log.e("source",source[i]+"");
        }
        //异常的处理 C++的的异常，JAVA 是无法try catch的,如果jni层面出现了异常，那么java的代码调用中止
//       try {
//           exception();
//       }catch (Exception e){
//           Log.e("exception",e.getMessage());
//
//       }
//        Log.e("exception","------------------------");

//        //缓存策略问题
//                for(int i=0;i<10;i++){
//                    cachede();
//                }
    }

    public String getName(){
        return "1234";
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String updateNameFromC();//属性访问
    public native String getMethod();//方法访问
    public native void getArray(int[] arrays);
    //引用解决的什么问题？什么通知JVM回收JNI的对象
    public native void getLocalReference();
    public native void exception();
    //缓存策略---对象的生命周期的
    public native void cachede();
    public native static void init();


}
