package com.example.hellojni.dagger2;

import com.example.hellojni.MainActivity;

import dagger.Component;

/**
 * Created by lenovo on 2017/12/4.
 */

@Component (modules = {UserModule.class})
public interface UserComponent {

    void inject(MainActivity activity);
}
