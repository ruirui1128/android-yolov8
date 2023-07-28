package com.tencent.yolov8ncnn;

import android.hardware.Camera;

/**
 * create by Rui on 2023-07-26
 * desc:
 */
public class CameraUtil {
    /**
     * 获取设备上可用的相机数量
     *
     * @return 可用的相机数量
     */
    public static int getNumberOfCameras() {
        return Camera.getNumberOfCameras();
    }

    /**
     * 获取相机的信息，包括 ID、摄像头朝向等
     *
     * @param cameraId 相机 ID
     * @return 相机的信息，若相机 ID 无效，则返回 null
     */
    public static Camera.CameraInfo getCameraInfo(int cameraId) {
        Camera.CameraInfo cameraInfo = new Camera.CameraInfo();
        try {
            Camera.getCameraInfo(cameraId, cameraInfo);
            return cameraInfo;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
