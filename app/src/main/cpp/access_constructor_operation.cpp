#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.access_constructor_operation"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_zpw_ndklibrary_MainActivity_invokeStringConstructors(JNIEnv *env, jobject thiz) {
    jclass stringClass;
    jmethodID cid;
    jcharArray elemArr;
    jstring result;

    // 创建string字符串
    jstring temp = env->NewStringUTF("this is char array");
    // jstring字符串转换为字节数组，作为构造Java String的参数
    const jchar *chars = env->GetStringChars(temp, NULL);
    int len = 10;

    // 找到具体的 String 类
    stringClass = env->FindClass("java/lang/String");
    if (stringClass == NULL) {
        return NULL;
    }

    // 找到具体的方法，([C)V 表示选择 String 的 String(char value[]) 构造方法
    cid = env->GetMethodID(stringClass, "<init>", "([C)V");
    if (cid == NULL) {
        return NULL;
    }

    // 字符串数组作为参数
    elemArr = env->NewCharArray(len);
    if (elemArr == NULL) {
        return NULL;
    }

    // 给字符串数组赋值
    env->SetCharArrayRegion(elemArr, 0, len, chars);
    // 使用NewObject创建类
    result = (jstring) env->NewObject(stringClass, cid, elemArr);
    env->DeleteLocalRef(elemArr);
    env->DeleteLocalRef(stringClass);
    return result;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_zpw_ndklibrary_MainActivity_allocObjectConstructor(JNIEnv *env, jobject thiz) {
    jclass animalClass;
    jobject result;
    jmethodID mid;

    animalClass = env->FindClass("com/zpw/ndklibrary/Animal");
    if (animalClass == NULL) {
        return NULL;
    }

    mid = env->GetMethodID(animalClass, "<init>", "(Ljava/lang/String;)V");
    if (mid == NULL) {
        return NULL;
    }

    jstring args = env->NewStringUTF("creat animal use AllocObject");

    // Jni提供了AllocObject 创建对象和CallNonvirtualVoidMethod调用构造方法来分步完成Java对象的构建
    result = env->AllocObject(animalClass);
    if (result == NULL) {
        return NULL;
    }

    env->CallNonvirtualVoidMethod(result, animalClass, mid, args);
    if (env->ExceptionCheck()) {
        env->DeleteLocalRef(result);
        return NULL;
    }
    return result;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_callSuperMethod(JNIEnv *env, jobject thiz) {
    jclass dog_cls;
    jmethodID dog_mid;
    jstring dog_name;
    jobject dog;

    dog_cls = env->FindClass("com/zpw/ndklibrary/Dog");
    if (dog_cls == NULL) {
        return;
    }

    dog_mid = env->GetMethodID(dog_cls, "<init>", "(Ljava/lang/String;)V");
    if (dog_mid == NULL) {
        return;
    }

    dog_name = env->NewStringUTF("this is dog name");

    dog = env->NewObject(dog_cls, dog_mid, dog_name);
    if (dog == NULL) {
        return;
    }

    jclass animal_cls;
    jmethodID animal_mid;

    animal_cls = env->FindClass("com/zpw/ndklibrary/Animal");
    if (animal_cls == NULL) {
        return;
    }

    animal_mid = env->GetMethodID(animal_cls, "getName", "()Ljava/lang/String;");
    if (animal_mid == NULL) {
        return;
    }

    jstring name = (jstring) env->CallNonvirtualObjectMethod(dog, animal_cls, animal_mid);
    if (name == NULL) {
        return;
    }

    LOGD(TAG, "getName method value is %s", env->GetStringUTFChars(name, NULL));
}