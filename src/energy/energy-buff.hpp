//
// Created by sleepingmachine on 2022/3/25.
//

#ifndef ABYSSAL_CV_2022_ENERGY_BUFF_HPP
#define ABYSSAL_CV_2022_ENERGY_BUFF_HPP

#include "../asset/RoboMasterConfig.hpp"
#include "../src/serial/serial-port.hpp"
#include "../src/armor/armor-identify.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

#include <vector>
#include <iostream>
#include <atomic>

class IdentifyEnergyBuff{
public:
    IdentifyEnergyBuff();
    ~IdentifyEnergyBuff() {};
    friend class ControlSwitch;

    static void EnergyBuffIdentifyStream(cv::Mat importSrc, int* sendData);
private:
    static int hmin_0;
    static int hmax_0;
    static int smin_0;
    static int smax_0;
    static int vmin_0;
    static int vmax_0;

    static int hmin_1;
    static int hmax_1;
    static int smin_1;
    static int smax_1;
    static int vmin_1;
    static int vmax_1;

    static int open;
    static int close;
    static int erode;
    static int dilate;

    static cv::Mat srcHSV;
    static cv::Mat maskHSV;
    static cv::Mat maskHSV_0;
    static cv::Mat maskHSV_1;
    static void ImagePreprocess(const cv::Mat &src);
};
#endif //ABYSSAL_CV_2022_ENERGY_BUFF_HPP
