//
// Created by sleepingmachine on 2022/3/25.
//

#include "control-switch.hpp"

extern std::atomic_bool CameraisOpen;

extern std::mutex mutex1;
extern std::mutex mutex2;

ControlSwitch::ControlSwitch() {}

int ControlSwitch::getFrameErrorCounter = 0;

cv::Mat ControlSwitch::src(480, 960, CV_8UC3);

void ControlSwitch::SwitchMode(cv::Mat *pFrame) {
    cv::Mat temp;
    while(CameraisOpen) {
        if (mutex1.try_lock()) {
            temp = *pFrame;
            mutex1.unlock();
        }
        temp.copyTo(src);
        //cv::cvtColor(src, src, cv::COLOR_RGB2BGR);
        if (src.empty()) {
            std::cout << "Get Frame Fail" << std::endl;
            if (getFrameErrorCounter < 3)
            {
                continue;
            }
            else{
                exit(0);
            }
        }

    }
}
