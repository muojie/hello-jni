package com.example.hellojni.dagger2;

import android.util.Log;

/**
 * Created by lenovo on 2017/12/5.
 */

public class UserManager {
    private static final String TAG = "UserManager";

    private ApiService mApiService;

    public UserManager(ApiService apiService) {
        mApiService = apiService;
    }

    public void login(){
        Log.d("UserManger","Login");

        mApiService.login();
    }

    public void register() {
        Log.d(TAG, "register");
        mApiService.register();
    }
}
