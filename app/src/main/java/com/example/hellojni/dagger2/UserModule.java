package com.example.hellojni.dagger2;

import android.util.Log;

import okhttp3.OkHttpClient;
import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;

/**
 * Created by lenovo on 2017/12/4.
 */

@Module
public class UserModule {
//    private final static String TAG = "UserModule";

    @Provides
    OkHttpClient provideOkHttp() {

        return new OkHttpClient().newBuilder().build();
    }

    @Provides
    public ApiService provideApiServiceForRelease(OkHttpClient client) {
        ApiService apiService = new ApiService(client);

        return apiService;
    }

    @Provides
    public UserManager provideUserManager(ApiService apiService) {
        return new UserManager(apiService);
    }
}
