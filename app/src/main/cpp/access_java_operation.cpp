#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.access_java_operation"

extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_accessInstanceFiled(JNIEnv *env, jobject thiz, jobject animal) {
    // 想要获取的字段 id
    jfieldID fid;
    // 字段对应的具体的值
    jstring jstr;
    // 将 Java 的字符串转换为 Native 的字符串
    const char *str;
    // 获取 Java 对象的类
    jclass cls = env->GetObjectClass(animal);
    fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    if (fid == NULL) {
        return;
    }
    // 获取字段对应的值
    jstr = (jstring)(env->GetObjectField(animal, fid));
    str = env->GetStringUTFChars(jstr, NULL);
    if (str == NULL) {
        return;
    }

    LOGD(TAG, "name is %s", str);
    env->ReleaseStringUTFChars(jstr, str);
    jstr = env->NewStringUTF("replaced name");
    if (jstr == NULL) {
        return;
    }

    env->SetObjectField(animal, fid, jstr);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_accessStaticField(JNIEnv *env, jobject thiz, jobject animal) {
    jfieldID fid;
    jint num;
    jclass cls = env->GetObjectClass(animal);
    fid = env->GetStaticFieldID(cls, "num", "I");
    if (fid == NULL) {
        return;
    }
    num = env->GetStaticIntField(cls, fid);
    LOGD(TAG, "get static field num is %d", num);
    env->SetStaticIntField(cls, fid, ++num);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_callInstanceMethod(JNIEnv *env, jobject thiz, jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetMethodID(cls, "callInstanceMethod", "(I)V");
    if (mid == NULL) {
        return;
    }
    env->CallVoidMethod(animal, mid, 2);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_callStaticMethod(JNIEnv *env, jobject thiz, jobject animal) {
    jclass cls =env->GetObjectClass(animal);
    jmethodID mid = env->GetStaticMethodID(cls, "callStaticMethod",
                                           "(Ljava/lang/String;)Ljava/lang/String;");
    if (mid == NULL) {
        return;
    }

    jstring jstr = env->NewStringUTF("jstring");
    env->CallStaticObjectMethod(cls, mid, jstr);
}