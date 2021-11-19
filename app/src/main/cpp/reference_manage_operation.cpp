#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.reference_manage_operation"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_zpw_ndklibrary_MainActivity_errorCacheUseLocalReference(JNIEnv *env, jobject thiz) {
    static jmethodID mid = NULL;
    static jclass cls = NULL;

    if (cls == NULL) {
        cls = env->FindClass("java/lang/String");
        if (cls == NULL) {
            return NULL;
        }
    } else {
        LOGD(TAG, "cls is not null but program will crash");
    }

    if (mid == NULL) {
        mid = env->GetMethodID(cls, "<init>", "([C)V");
        if (mid == NULL) {
            return NULL;
        }
    } else {
        LOGD(TAG, "mid is not null but program will crash");
    }

    jcharArray charElem = env->NewCharArray(10);
    const jchar *j_char = env->GetStringChars(env->NewStringUTF("LocalReference"), NULL);
    env->SetCharArrayRegion(charElem, 0, 10, j_char);
    jstring result = (jstring) env->NewObject(cls, mid, charElem);
    env->DeleteLocalRef(charElem);
    return result;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_zpw_ndklibrary_MainActivity_cacheWithGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass stringClass = NULL;
    if (stringClass == NULL) {
        jclass localRefs = env->FindClass("java/lang/String");
        if (localRefs == NULL) {
            return NULL;
        }
        stringClass = (jclass) env->NewGlobalRef(localRefs);
        env->DeleteLocalRef(localRefs);
        if (stringClass == NULL) {
            return NULL;
        }
    } else {
        LOGD(TAG, "use stringClass cached");
    }

    static jmethodID stringMid = NULL;
    if (stringMid == NULL) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (stringMid == NULL) {
            return NULL;
        }
    } else {
        LOGD(TAG, "use method cached");
    }

    jstring str = env->NewStringUTF("string");
    return (jstring) env->NewObject(stringClass, stringMid, str);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_useWeakGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass stringClass = NULL;
    if (stringClass == NULL) {
        jclass localRefs = env->FindClass("java/lang/String");
        if (localRefs == NULL) {
            return;
        }
        stringClass = (jclass) env->NewWeakGlobalRef(localRefs);
        if (stringClass == NULL) {
            return;
        }
    }

    static jmethodID stringMid = NULL;
    if (stringMid == NULL) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (stringMid == NULL) {
            return;
        }
    }

    jboolean isGC = env->IsSameObject(stringClass, NULL);
    if (isGC) {
        LOGD(TAG, "weak reference has been gc");
    } else {
        jstring str = (jstring) env->NewObject(stringClass, stringMid,
                                               env->NewStringUTF("jstring"));
        LOGD(TAG, "str is %s", env->GetStringUTFChars(str, NULL));
    }
}