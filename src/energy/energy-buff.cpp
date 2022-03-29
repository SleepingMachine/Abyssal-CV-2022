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
int IdentifyEnergyBuff::close = 6;
int IdentifyEnergyBuff::erode = 2;
int IdentifyEnergyBuff::dilate = 4;

cv::RotatedRect IdentifyEnergyBuff::rLogoRect;

std::vector<std::vector<cv::Point2i> > IdentifyEnergyBuff::allContours;
std::vector<cv::Vec4i> IdentifyEnergyBuff::hierarchy;

std::vector<cv::RotatedRect> IdentifyEnergyBuff::possibleRects;
std::vector<float> IdentifyEnergyBuff::possibleCoutoursArea;
std::vector<cv::RotatedRect> IdentifyEnergyBuff::possibleRLogoRects;

static EnergyBuffPara energyBuffPara = EnergyBuffParaFactory::getEnergyBuffPara();

cv::Mat IdentifyEnergyBuff::srcHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_0(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_1(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::dstHSV(640, 960, CV_8UC3);

void IdentifyEnergyBuff::EnergyBuffIdentifyStream(cv::Mat importSrc, int *sendData) {

    ImagePreprocess(importSrc);
    searchContours_RLogoRect(possibleRects, possibleCoutoursArea);
    searchContours_BuffCenter(possibleRLogoRects);
    for (int i = 0; i < possibleRLogoRects.size(); ++i) {
        EnergyBuffTool::drawRotatedRect(importSrc,possibleRLogoRects[i],cv::Scalar(51,48,245),2, 16);
    }

    cv::imshow("energy1", importSrc);
    cv::imshow("energy", dstHSV);

    resourceRelease();
}

void IdentifyEnergyBuff::ImagePreprocess(const cv::Mat &src) {
    cv::cvtColor(src, srcHSV, CV_BGR2HSV, 0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_0, IdentifyEnergyBuff::smin_0, IdentifyEnergyBuff::vmin_0), cv::Scalar(IdentifyEnergyBuff::hmax_0, IdentifyEnergyBuff::smax_0, IdentifyEnergyBuff::vmax_0), maskHSV_0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_1, IdentifyEnergyBuff::smin_1, IdentifyEnergyBuff::vmin_1), cv::Scalar(IdentifyEnergyBuff::hmax_1, IdentifyEnergyBuff::smax_1, IdentifyEnergyBuff::vmax_1), maskHSV_1);
    //cv::imshow("0", maskHSV_0);
    //cv::imshow("1", maskHSV_1);
    maskHSV = maskHSV_0 | maskHSV_1;
    morphologyEx(maskHSV, dstHSV, 2, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::open,IdentifyEnergyBuff::open)));
    morphologyEx(dstHSV, dstHSV, 3, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::close,IdentifyEnergyBuff::close)));
    morphologyEx(dstHSV, dstHSV, 0, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::erode,IdentifyEnergyBuff::erode)));
    morphologyEx(dstHSV, dstHSV, 1, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::dilate,IdentifyEnergyBuff::dilate)));
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

void IdentifyEnergyBuff::searchContours_RLogoRect(std::vector<cv::RotatedRect> &rects, std::vector<float> &areas) {
    cv::findContours(dstHSV, allContours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    std::vector<std::vector<cv::Point2i> >::iterator it = allContours.begin();
    int i = 0;
    while (it != allContours.end()) {
        cv::RotatedRect scanRect = minAreaRect(*it);   //检测最小面积的矩形
        float area = float(cv::contourArea(allContours[i]));
        i++;
        ++it;
        float longSide = EnergyBuffTool::findExtremumOfSide(scanRect, LONG_SIDE);
        float shortSide = EnergyBuffTool::findExtremumOfSide(scanRect, SHORT_SIDE);

        if (longSide < shortSide * 1.2) {
            possibleRLogoRects.push_back(scanRect);
            //continue;
        }
        if (scanRect.size.area() <= 2 * rLogoRect.size.area()) {
            continue;
        }
        rects.push_back(scanRect);
        areas.push_back(area);
    }
}

void IdentifyEnergyBuff::resourceRelease() {
    allContours.clear();
    hierarchy.clear();
    possibleRects.clear();
    possibleCoutoursArea.clear();
    possibleRLogoRects.clear();
}

void IdentifyEnergyBuff::searchContours_BuffCenter(std::vector<cv::RotatedRect> possibleRLogoRects) {
    //如果轮廓容量为零则返回
    //_findRectFlag = false;
    if (IdentifyEnergyBuff::possibleRLogoRects.empty()) {
        return;
    }
    //bool findFlag = false;

    //筛选圆心矩形

    for (int i = 0; i < possibleRLogoRects.size(); i++) {
        if (possibleRLogoRects[i].size.area() < energyBuffPara.minBuffCenterRectArea) {
            continue;
        }
        //如果轮廓不是类正方形，则跳过
        if ((possibleRLogoRects[i].size.width / possibleRLogoRects[i].size.height) > 1.2 ||
            (possibleRLogoRects[i].size.width / possibleRLogoRects[i].size.height) < 0.8) {
            continue;
        }
        rLogoRect = possibleRLogoRects[i];
        /*
        possibleCircles.push_back(buffRects[i]);
        //如果SVM判断错误，则跳过
        if (!circleCenterSVM(buffRects[i])) {
            continue;
        }
        //找出与圆心后确定圆心矩形长和宽
        circleCenterRect = buffRects[i];
        findFlag = true;
        break;
    }
    if (!findFlag) {
        for (int i = 0; i < possibleCircles.size(); i++) {
            if (fabs(possibleCircles[i].size.area() - _circleCenterArea) < 30) {
                circleCenterRect = possibleCircles[i];
                findFlag = true;
                break;
            }
        }
    }
    if (!findFlag) {
        _findRectFlag = false;
    } else {
        if (circleCenterRect.size.width > circleCenterRect.size.height) {
            _circleCenterLong = circleCenterRect.size.width;
        } else {
            _circleCenterLong = circleCenterRect.size.height;
        }
        _circleCenterArea = circleCenterRect.size.area();
        _R_2D_Center = circleCenterRect.center;
        _findRectFlag = true;
        ++_find_cnt;
    }*/
        //Util::drawRectShow(_src.clone(), circleCenterRect);
    }
}
