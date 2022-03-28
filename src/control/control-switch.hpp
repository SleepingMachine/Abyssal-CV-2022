//
// Created by sleepingmachine on 2022/3/25.
//

#ifndef ABYSSAL_CV_2022_CONTROL_SWITCH_HPP
#define ABYSSAL_CV_2022_CONTROL_SWITCH_HPP

#include <opencv2/core/mat.hpp>
#include <atomic>
#include <iostream>
#include "../asset/RoboMasterConfig.hpp"
#include "../src/armor/armor-identify.hpp"
#include "../src/energy/energy-buff.hpp"

class ControlSwitch{
public:
    ControlSwitch();
    ~ControlSwitch() {};
    static FunctionConfig functionConfig;

    static void SwitchMode(cv::Mat *pFrame);
private:
    static int sendData;
    static int lastMode;
    static cv::Mat src;
    static int getFrameErrorCounter;
    static void initColorThresholdParameters();
};

#endif //ABYSSAL_CV_2022_CONTROL_SWITCH_HPP
