#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.thread_operation"

static JavaVM *gVm = NULL;

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    gVm = vm;
    return JNI_VERSION_1_6;
}

void *printThreadHello(void *);
void *printThreadHello(void *) {
    LOGD(TAG, "hello thread");
    // 切记要有返回值
    return NULL;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handles; // 线程句柄
    int result = pthread_create(&handles, NULL, printThreadHello, NULL);
    if (result != 0) {
        LOGD(TAG, "create thread failed");
    } else {
        LOGD(TAG, "create thread success");
    }
}