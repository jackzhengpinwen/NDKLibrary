#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.cache_field_method_operation"

extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_staticCacheField(JNIEnv *env, jobject thiz, jobject animal) {
    static jfieldID fid = NULL;
    static int count = 0;
    jclass cls = env->FindClass("com/zpw/ndklibrary/Animal");
    jstring jstr;
    const char *c_str;
    // 从缓存中查找
    if (fid == NULL) {
        fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
        LOGD(TAG, "field id is created", "");
        if (fid == NULL) {
            return;
        }
    } else {
        LOGD(TAG, "field id is cached %d", ++count);
    }

    jstr = (jstring) env->GetObjectField(animal, fid);
    c_str = env->GetStringUTFChars(jstr, NULL);
    if (c_str == NULL) {
        return;
    }

    env->ReleaseStringUTFChars(jstr, c_str);
    jstr = env->NewStringUTF("new name");
    if (jstr == NULL) {
        return;
    }

    env->SetObjectField(animal, fid, jstr);
}

// 全局变量，作为缓存方法 id
jmethodID InstanceMethodCache;

extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_Animal_init(JNIEnv *env, jclass clazz) {
    jclass cls = env->FindClass("com/zpw/ndklibrary/Animal");
    InstanceMethodCache = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    LOGD(TAG, "Animal_init");
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_callCacheMethod(JNIEnv *env, jobject thiz, jobject animal) {
    jstring name = (jstring) env->CallObjectMethod(animal, InstanceMethodCache);
    const char *c_name = env->GetStringUTFChars(name, NULL);
    LOGD(TAG, "call cache method and value is %s", c_name);
}