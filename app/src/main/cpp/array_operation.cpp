#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(TAG, FMT, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FMT, ##args)

#define TAG "jni.array_operation"

extern "C"
JNIEXPORT jint JNICALL
Java_com_zpw_ndklibrary_MainActivity_getNativeArray(JNIEnv *env, jobject thiz, jintArray intArray_,
                                                    jint num) {
    jint *intArray;
    int sum = 0;
    // 如同 getUTFString 一样，会申请 native 内存
    intArray = env->GetIntArrayElements(intArray_, NULL);
    if (intArray == NULL) {
        return 0;
    }
    jsize arrayLength = env->GetArrayLength(intArray_);
    LOGD(TAG, "array length is %d", arrayLength);

    for (int i = 0; i < arrayLength; i++) {
        sum += intArray[i];
    }
    LOGD(TAG, "sum is %d", sum);

    // 通过 GetIntArrayRegion 方法来获取数组内容
    jint buf[num];
    env->GetIntArrayRegion(intArray_, 0, num, buf);
    sum = 0;
    for (int i = 0; i < num; i++) {
        sum += buf[i];
    }
    LOGD(TAG, "sum is %d", sum);

    env->ReleaseIntArrayElements(intArray_, intArray, 0);
    return sum;
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_zpw_ndklibrary_MainActivity_getIntArray(JNIEnv *env, jobject thiz, jint num) {
    jintArray intArray = env->NewIntArray(num);
    jint buf[num];
    for (int i = 0; i < num; i++) {
        buf[i] = i * 2;
    }
    env->SetIntArrayRegion(intArray, 0, num, buf);
    return intArray;
}
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_zpw_ndklibrary_MainActivity_getTwoDimensionalArray(JNIEnv *env, jobject thiz, jint size) {
    // 声明一个对象数组
    jobjectArray result;
    // 找到对象数组中具体的对象类型,[I 指的就是数组类型
    jclass intArrayCls = env->FindClass("[I");
    if (intArrayCls == NULL) {
        return NULL;
    }

    // 相当于初始化一个对象数组，用指定的对象类型
    result = env->NewObjectArray(size, intArrayCls, NULL);
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        // 用来给整型数组填充数据的缓冲区
        jint tmp[256];
        // 声明一个整型数组
        jintArray iarr = env->NewIntArray(size);
        if (iarr == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        // 给整型数组填充数据
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        // 给对象数组指定位置填充数据，这个数据就是一个一维整型数组
        env->SetObjectArrayElement(result, i, iarr);
        // 释放局部引用
        env->DeleteLocalRef(iarr);
    }
    return result;
}

/** * 打印对象数组中的信息 */ extern "C" JNIEXPORT void JNICALL
Java_com_zpw_ndklibrary_MainActivity_printAnimalsName(JNIEnv *env, jobject instance,
                                                                  jobjectArray animals) {
    jobject animal;
    // 数组长度
    int size = env->GetArrayLength(animals);
    // 数组中对应的类
    jclass cls = env->FindClass("com/zpw/ndklibrary/Animal");
    // 类对应的字段描述
    jfieldID fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    // 类的字段具体的值
    jstring jstr;
    // 类字段具体值转换成 C/C++ 字符串
    const char *str;
    for (int i = 0; i < size; ++i) {
        // 得到数组中的每一个元素
        animal = env->GetObjectArrayElement(animals, i);
        // 每一个元素具体字段的值
        jstr = (jstring) (env->GetObjectField(animal, fid));
        str = env->GetStringUTFChars(jstr, NULL);
        if (str == NULL) {
            continue;
        }
        LOGD(TAG, "name is %s", str);
        env->ReleaseStringUTFChars(jstr, str);
    }
}
