//
// Created by sleepingmachine on 2022/3/25.
//

#ifndef ABYSSAL_CV_2022_ENERGY_BUFF_HPP
#define ABYSSAL_CV_2022_ENERGY_BUFF_HPP

#include "../asset/RoboMasterConfig.hpp"
#include "../src/serial/serial-port.hpp"

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

    static void EnergyBuffIdentifyStream(cv::Mat importSrc, int* sendData);
private:
    static cv::Mat src;
};
#endif //ABYSSAL_CV_2022_ENERGY_BUFF_HPP
