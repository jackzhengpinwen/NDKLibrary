#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.basic_operation"

/**
 * JNIEnv* 是是一个指针，通过它可以访问虚拟机中的各种数据结构，同时它还指向JVM函数表的指针，函数表中的每个入口指向一个JNI函数，
 * 每个函数用于访问JVM中特定的数据结构。
 *
 * jobject 是 native 函数里的第二个参数类型，但却不是一定的。
 * 如果该 native 方法是一个静态 static 方法，那么第二个参数就是 jobject 类型，指的是调用该函数的对象；
 * 如果是一个实例方法，那么第二个参数就是 jclass 类型，指的是调用该函数的类。
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_zpw_ndklibrary_MainActivity_getNativeString(JNIEnv *env, jobject thiz, jstring str_) {
    // Java 默认使用 Unicode 编码，而 C/C++ 默认使用 UTF 编码。

    // 生成 jstring 类型的字符串
    jstring returnValue = env->NewStringUTF("hello native string");

    // 获得 Unicode 编码的字符串的长度
    jsize jStringLength = env->GetStringLength(str_);
    LOGD(TAG, "jstring length = %d", jStringLength);

    // 获得指定范围的字符串内容
    jchar inbuf[128];
    env->GetStringRegion(str_, 0, jStringLength, inbuf);
    LOGD(TAG, "jstring is %s", inbuf);

    // 将 jstring 类型的字符串转换为 C 风格的字符串，会额外申请内存
    const char *str = env->GetStringUTFChars(str_, NULL);
    if (str == NULL) {
        return NULL;
    }
    LOGD(TAG, "java string = %s", str);

    // 释放掉申请的 C 风格字符串的内存
    env->ReleaseStringUTFChars(str_, str);
    return returnValue;
}