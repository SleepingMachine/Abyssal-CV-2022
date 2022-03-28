//
// Created by sleepingmachine on 2022/3/25.
//

#include "energy-buff.hpp"

//默认hsv颜色阈值

int IdentifyEnergyBuff::hmin_0 = 53;
int IdentifyEnergyBuff::hmax_0 = 148;
int IdentifyEnergyBuff::smin_0 = 128;
int IdentifyEnergyBuff::smax_0 = 255;
int IdentifyEnergyBuff::vmin_0 = 98;
int IdentifyEnergyBuff::vmax_0 = 255;

int IdentifyEnergyBuff::hmin_1 = 53;
int IdentifyEnergyBuff::hmax_1 = 148;
int IdentifyEnergyBuff::smin_1 = 128;
int IdentifyEnergyBuff::smax_1 = 255;
int IdentifyEnergyBuff::vmin_1 = 98;
int IdentifyEnergyBuff::vmax_1 = 255;

//默认二值化操作阈值
int IdentifyEnergyBuff::open = 1;
int IdentifyEnergyBuff::close = 18;
int IdentifyEnergyBuff::erode = 3;
int IdentifyEnergyBuff::dilate = 6;

cv::Mat IdentifyEnergyBuff::srcHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_0(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_1(640, 960, CV_8UC3);

void IdentifyEnergyBuff::EnergyBuffIdentifyStream(cv::Mat importSrc, int *sendData) {

    ImagePreprocess(importSrc);

    cv::imshow("energy", maskHSV);
}

void IdentifyEnergyBuff::ImagePreprocess(const cv::Mat &src) {
    cv::cvtColor(src, srcHSV, CV_BGR2HSV, 0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_0, IdentifyEnergyBuff::smin_0, IdentifyEnergyBuff::vmin_0), cv::Scalar(IdentifyEnergyBuff::hmax_0, IdentifyEnergyBuff::smax_0, IdentifyEnergyBuff::vmax_0), maskHSV_0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_1, IdentifyEnergyBuff::smin_1, IdentifyEnergyBuff::vmin_1), cv::Scalar(IdentifyEnergyBuff::hmax_1, IdentifyEnergyBuff::smax_1, IdentifyEnergyBuff::vmax_1), maskHSV_1);
    //cv::imshow("0", maskHSV_0);
    //cv::imshow("1", maskHSV_1);
    maskHSV = maskHSV_0 | maskHSV_1;
}

