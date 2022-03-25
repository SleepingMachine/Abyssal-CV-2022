//
// Created by sleepingmachine on 2022/3/25.
//

#include "energy-buff.hpp"

cv::Mat IdentifyEnergyBuff::src(480, 960, CV_8UC3);

void IdentifyEnergyBuff::EnergyBuffIdentifyStream(cv::Mat importSrc, int *sendData) {
    src = importSrc;
    cv::imshow("energy", src);
}

