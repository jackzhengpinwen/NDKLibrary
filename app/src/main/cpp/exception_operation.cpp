#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.exception_operation"


extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_exceptionDealer(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/zpw/ndklibrary/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, mid);
    mid = env->GetMethodID(cls, "exceptionFun", "()I");
    // 先初始化一个类，然后调用类方法，就如文章中描述的那样
    env->CallIntMethod(obj, mid);
    //检查是否发生了异常
    jthrowable exc = env->ExceptionOccurred();
    if (exc) {
        // 打印异常日志
        env->ExceptionDescribe();
        // 这行代码才是关键不让应用崩溃的代码，
        env->ExceptionClear();
        // 发生异常了要记得释放资源
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(obj);
    }
}

void throwByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = env->FindClass(name);
    if (cls != NULL) {
        env->ThrowNew(cls, msg);
    }
    env->DeleteLocalRef(cls);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_nativeThrowException(JNIEnv *env, jobject thiz) {
    throwByName(env, "java/lang/IllegalArgumentException", "native throw exception");
}