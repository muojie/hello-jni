#include <jni.h>
#include <string>
#include "stdlib.h"
#include "string.h"
#include <android/log.h>

#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


//首先将a强制声明为指向整数的指针，读取指针对应的整数
int compare(const void*a, const void*b){
    return (*(int*)a - *(int*)b);
}
/**
 * 真实企业开发，做成员变量的初始化
 */

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojni_MainActivity_init(JNIEnv *env, jclass type) {
    static jfieldID jfieldID1 = NULL; //局部静态变量（访问内存空间） //第一种办法
    if (jfieldID1 == NULL) {
        jfieldID1 = env->GetFieldID(type, "name", "Ljava/lang/String;");
        LOGI("---------GetFieldID-------\n");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojni_MainActivity_cachede(JNIEnv *env, jobject instance) {
    jclass _jclass = env->GetObjectClass(instance);

    static jfieldID jfieldID1 = NULL; //局部静态变量（访问内存空间） //第一种办法
    if (jfieldID1 == NULL) {
        jfieldID1 = env->GetFieldID(_jclass, "name", "Ljava/lang/String;");
        LOGI("---------GetFieldID-------\n");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojni_MainActivity_exception(JNIEnv *env, jobject instance) {
   //构建一个异常
    jclass _jcalss = env->GetObjectClass(instance);
    jfieldID jfieldID1 = env->GetFieldID(_jcalss,"name2","Ljava/lang/String;");
    //检测异常
    jthrowable _jthrowable = env->ExceptionOccurred();
    if(_jthrowable!=NULL){
        //为了保证java的代码能继续执行，清除异常
        env->ExceptionClear();
        jfieldID1 = env->GetFieldID(_jcalss,"name","Ljava/lang/String;");
    }
    jstring  _jstring = (jstring) env->GetObjectField(instance, jfieldID1);
    char* str = (char *) env->GetStringUTFChars(_jstring, NULL);
    //假使c++有异常，java层面如何try
    //int strcmp(const char* _Nonnull, const char* _Nonnull) __attribute_pure__;
    if(strcmp(str,"www")!=0){
        //抛出异常（java的异常
        // ）
        jclass  newThrow = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(newThrow,"非法参数");
    }


}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojni_MainActivity_getLocalReference(JNIEnv *env, jobject instance) {
    //模拟循环
    for(int i=0;i<100;i++){
       jclass _jcalss =  env->FindClass("java/util/Date");
       jobject _jobj = env->NewObject(_jcalss,env->GetMethodID(_jcalss,"<init>","()V"));
        //00000对象操作
        env->DeleteLocalRef(_jobj);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_hellojni_MainActivity_getArray(JNIEnv *env, jobject instance, jintArray arrays_) {
    jclass _jcalss = env->GetObjectClass(instance);
    jfieldID jfieldID1 = env->GetFieldID(_jcalss,"name","Ljava/lang/String;");
    jint *arrays = env->GetIntArrayElements(arrays_, NULL);
    //获取数组长度
    int _len = env->GetArrayLength(arrays_);
    //void qsort(void*, size_t, size_t, int (*)(const void*, const void*));
    qsort(arrays,_len, sizeof(int),compare);
    env->ReleaseIntArrayElements(arrays_, arrays, 0);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_MainActivity_getMethod(JNIEnv *env, jobject instance) {
    jclass _jclass = env->GetObjectClass(instance);
    //jclass clazz, const char* name, const char* sig)
    jmethodID _jmethodID = env->GetMethodID(_jclass,"getName","()Ljava/lang/String;");//属性
    //jni 调用java的方法
    jstring str = (jstring) env->CallObjectMethod(instance, _jmethodID);
    char* tempstr = (char*)env->GetStringUTFChars(str, NULL);
    char text[20] = "success";
    char* finresult = strcat(tempstr,text);
    return env->NewStringUTF(finresult);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_MainActivity_updateNameFromC(JNIEnv *env, jobject instance) {
    //jobject代表的是什么？ MainActivity这个类的对象 首先获取jclass
    jclass _jclass = env->GetObjectClass(instance);
    //jclass clazz, const char* name, const char* sig)
    jfieldID _jfieldID = env->GetFieldID(_jclass,"name","Ljava/lang/String;");//属性
    //(jobject obj, jfieldID fieldID)
    jstring result = (jstring) env->GetObjectField(instance, _jfieldID);//开辟一个内存空间
    printf("%#x\n",result);
    //如何去装换成java string
    char* str = (char*)env->GetStringUTFChars(result, NULL);
    char text[20] = "success";
    char* finresult = strcat(str,text);
    //(const char* bytes)
    return env->NewStringUTF(finresult);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
