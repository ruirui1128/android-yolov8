//
// Created by rui on 2023-07-25.
//
#include "hepler.h"

Helper::Helper() {

}

void Helper::init(JavaVM *vm) {
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "=======执行Helper::init===========");
    g_jvm = vm;
}

// 调用原生android 方法
void Helper::update2Android(std::vector<com::tencent::yolov8ncnn::Object> objects) {
    JNIEnv *env = this->getJNIEnv();
    // 获取当前线程的 JNIEnv
    if (env == NULL) {
        return; // 获取 JNIEnv 失败
    }
    // 获取 Java 的 ArrayList 类引用
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add",
                                                    "(Ljava/lang/Object;)Z");

    // 创建 Java 的 ArrayList 对象
    jobject arrayListObject = env->NewObject(arrayListClass, arrayListConstructor);
    if (g_objectClass == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "ncnn", "没有找到java中的Object");
        return;
    }
    jmethodID objectConstructor = env->GetMethodID(g_objectClass, "<init>", "(IF)V");
    env->GetMethodID(g_objectClass, "getLabel", "()I");
    env->GetMethodID(g_objectClass, "getProb", "()F");

    // 将 std::vector<Object> 中的元素逐个转换为 Java 的 Object 对象，并添加到 ArrayList 中
    for (const auto &object: objects) {
        // 创建 Java 的 Object 对象
        jobject objectObject = env->NewObject(g_objectClass, objectConstructor,
                                              object.label,
                                              object.prob);
        // 添加 Object 对象到 ArrayList
        env->CallBooleanMethod(arrayListObject, arrayListAddMethod, objectObject);
        // 删除局部引用
        env->DeleteLocalRef(objectObject);
    }

    // 调用 Java 方法，并将 ArrayList 对象作为参数传递
    jclass javaClass = env->GetObjectClass(g_thiz);
    jmethodID javaMethodID = env->GetMethodID(javaClass, "processObjects",
                                              "(Ljava/util/ArrayList;)V");
    env->CallVoidMethod(g_thiz, javaMethodID, arrayListObject);

    // 删除局部引用
    env->DeleteLocalRef(arrayListObject);


}

// 通过过全局的JVM 找到当前线程jniEnv
JNIEnv *Helper::getJNIEnv() {
    JNIEnv *env;
    int getEnvStat = g_jvm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (getEnvStat == JNI_EDETACHED) {
        // 如果当前线程未附加到 Java VM，需要调用 AttachCurrentThread 进行附加
        __android_log_print(ANDROID_LOG_DEBUG, "ncnn", " 如果当前线程未附加到 Java VM");
        if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "当前线程未附加到 Java VM===失败");
            return NULL;
        }
    } else if (getEnvStat == JNI_EVERSION) {
        // JNI 版本不支持
        __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "当前线程未附加到 JNI 版本不支持");
        return NULL;
    }
    return env;
}

void Helper::initGlobal(jclass g_jclass, jobject thiz) {
    g_objectClass = g_jclass;
    g_thiz = thiz;
}

void Helper::release() {
    JNIEnv *pEnv = getJNIEnv();
    if (pEnv) {
        pEnv->DeleteGlobalRef(g_objectClass);
        pEnv->DeleteGlobalRef(g_thiz);
        g_thiz = NULL;
        g_objectClass = NULL;
    }

}


