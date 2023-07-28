// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

package com.tencent.yolov8ncnn;

import static android.content.ContentValues.TAG;

import android.content.res.AssetManager;
import android.util.Log;
import android.view.Surface;

import java.util.ArrayList;
import java.util.Vector;

public class Yolov8Ncnn {
    public native boolean loadModel(AssetManager mgr, int modelid, int cpugpu);

    public native boolean openCamera(int facing);

    public native boolean closeCamera();

    public native boolean setOutputWindow(Surface surface);

    public native void detect(boolean start);  //开启或关闭绘制框

    public native void initGlobalObj();    // 全局化 jclass 和 jobject

    public native boolean getDetect();     // 获取 detect 状态

    public native void callNativeMethod();


    static {
        System.loadLibrary("yolov8ncnn");
    }


    public void addNub(int x, int y) {
        Log.e("Yolov8Ncnn", "==Yolov8Ncnn=====获取原生数据:" + x + "======threadId:" + Thread.currentThread().getId());
    }


    /**
     * jni 调用的方法
     * 将 native层数据返回给java
     */
    public void processObjects(ArrayList<Object> objects) {
        // 在这里处理处理 jni 传过来 objects
        for (Object obj : objects) {
            // 处理每个 Object 对象
            Log.e(TAG, Thread.currentThread().getId() + "   Yolov8Ncnn======obj:" + obj.toString());
        }
    }
}
