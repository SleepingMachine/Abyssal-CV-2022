//
// Created by sleepingmachine on 2021/11/30.
//
#ifndef ABYSSAL_2022_CAMERA_STREAM_H
#define ABYSSAL_2022_CAMERA_STREAM_H

#include "camera/CameraApi.h" //相机SDK的API头文件
#include "../asset/RoboMasterConfig.hpp"
#include "../src/control/control-switch.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <mutex>
#include <atomic>

#include <stdio.h>

class CameraStream{
public:
    static int InitCamera();
    static void StreamRetrieve(cv::Mat* pFrame);
    static void UnInitCamera();
    static int SetCameraResolution(int hCamera, int offsetx, int offsety, int width, int height);
};
#endif //ABYSSAL_2022_CAMERA_STREAM_H

