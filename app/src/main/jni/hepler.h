//
// Created by rui on 2023-07-25.
//

#ifndef NCNN_ANDROID_YOLOV8_HEPLER_H
#define NCNN_ANDROID_YOLOV8_HEPLER_H

#include <jni.h>
#include "yolo.h"
#include <android/log.h>

class Helper {
public:
    Helper();
    /**
     *
     * @param vm  用于JVN全局
     */
    void init(JavaVM *vm);

    /**
     *
     * @param g_jclass 全局化jclass
     * @param thiz     全局化jobject
     */
    void initGlobal(jclass g_jclass ,jobject thiz);

    /**
     * 通过jvm 获取当前线程的jniEnv
     */
    JNIEnv *getJNIEnv();

    /**
     * 将jni层数据传递给java层
     * @param vector
     */
    void update2Android(std::vector<com::tencent::yolov8ncnn::Object> vector);

    /**
     * 销毁
     */
    void release();

private:
    JavaVM *g_jvm = NULL;
    jclass g_objectClass = NULL;
    jobject g_thiz = NULL;
};

#endif //NCNN_ANDROID_YOLOV8_HEPLER_H
