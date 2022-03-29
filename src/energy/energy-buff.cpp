//
// Created by sleepingmachine on 2022/3/25.
//

#include "energy-buff.hpp"

//默认hsv颜色阈值

int IdentifyEnergyBuff::hmin_0 = 0;
int IdentifyEnergyBuff::hmax_0 = 0;
int IdentifyEnergyBuff::smin_0 = 0;
int IdentifyEnergyBuff::smax_0 = 0;
int IdentifyEnergyBuff::vmin_0 = 0;
int IdentifyEnergyBuff::vmax_0 = 0;

int IdentifyEnergyBuff::hmin_1 = 0;
int IdentifyEnergyBuff::hmax_1 = 0;
int IdentifyEnergyBuff::smin_1 = 0;
int IdentifyEnergyBuff::smax_1 = 0;
int IdentifyEnergyBuff::vmin_1 = 0;
int IdentifyEnergyBuff::vmax_1 = 0;

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

    cv::imshow("energy1", importSrc);
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

void IdentifyEnergyBuff::CreatTrackbars() {
    cv::namedWindow("能量机关识别中的阈值调整",cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("hmin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmin_0, 255,NULL);
    cv::createTrackbar("hmax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmax_0, 255,NULL);
    cv::createTrackbar("smin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smin_0, 255,NULL);
    cv::createTrackbar("smax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smax_0, 255,NULL);
    cv::createTrackbar("vmin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmin_0, 255,NULL);
    cv::createTrackbar("vmax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmax_0, 255,NULL);

    cv::createTrackbar("hmin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmin_1, 255,NULL);
    cv::createTrackbar("hmax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmax_1, 255,NULL);
    cv::createTrackbar("smin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smin_1, 255,NULL);
    cv::createTrackbar("smax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smax_1, 255,NULL);
    cv::createTrackbar("vmin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmin_1, 255,NULL);
    cv::createTrackbar("vmax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmax_1, 255,NULL);

    cv::createTrackbar("open", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::open, 10,NULL);
    cv::createTrackbar("close", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::close, 30,NULL);
    cv::createTrackbar("erode", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::erode, 10,NULL);
    cv::createTrackbar("dilate", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::dilate, 20,NULL);
}

