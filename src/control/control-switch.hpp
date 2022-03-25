//
// Created by sleepingmachine on 2022/3/25.
//

#ifndef ABYSSAL_CV_2022_CONTROL_SWITCH_HPP
#define ABYSSAL_CV_2022_CONTROL_SWITCH_HPP

#include <opencv2/core/mat.hpp>
#include <atomic>
#include <iostream>

class ControlSwitch{
public:
    ControlSwitch();
    ~ControlSwitch() {};
private:
    static cv::Mat src;
    static int getFrameErrorCounter;
    static void SwitchMode(cv::Mat *pFrame);
};

#endif //ABYSSAL_CV_2022_CONTROL_SWITCH_HPP
