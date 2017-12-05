package com.example.hellojni.dagger2;

import android.util.Log;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;

/**
 * Created by lenovo on 2017/12/4.
 */

public class ApiService {
    private static final String TAG = "ApiService";

    public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

    OkHttpClient mOkHttpClient;

    public ApiService() {
        Log.e(TAG, "new ApiService()");
    }

    public ApiService(OkHttpClient httpClient) {
        Log.e(TAG, "new ApiService(OkHttpClient httpClient)");
        mOkHttpClient = httpClient;
    }

    public void register() {
        Log.d(TAG, "register: " + mOkHttpClient);
    }

    public void login() {
        Log.d(TAG, "login");
    }
}
