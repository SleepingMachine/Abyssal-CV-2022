//
// Created by sleepingmachine on 2022/1/9.
//
#ifndef ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP
#define ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP

#include "../asset/RoboMasterConfig.hpp"
#include "../src/serial/serial-port.hpp"
#include "armor-tool.hpp"
#include "KCF/armor-KCF.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

#include <vector>
#include <iostream>
#include <atomic>

class IdentifyArmor{

public:
    struct ArmorStruct {
        cv::RotatedRect partLightBars[2];
        cv::RotatedRect armorRect;
        float lightAngle;
        bool armorType = false;
        int carId = 0;
        cv::Point2f hitPoint;
    };
    friend class ArmorKCF;

private:
    static int getFrameErrorCounter;
    static cv::Mat src;
    static cv::Mat searchSrc;
    static cv::Mat srcHSV;
    static cv::Mat maskHSV;
    static cv::Mat dstHSV;

    static int hmin;
    static int hmax;
    static int smin;
    static int smax;
    static int vmin;
    static int vmax;
    static int open;
    static int close;
    static int erode;
    static int dilate;

    static double roiScalingRatio_x;
    static double roiScalingRatio_y;

    static bool _cropRoi;
    static bool _enableRoiScaling;
    static bool _roiScaling;

    static int targetArmorIdex;

    static std::vector<std::vector<cv::Point2i>> allContours;
    static std::vector<cv::Vec4i> hierarchy;
    static std::vector<cv::RotatedRect> filteredLightBars;
    static std::vector<ArmorStruct> armorStructs;
    static cv::Rect lastArmorTarget;
    static cv::Rect2d restoreRect;

    static cv::Point cropOriginPoint;

    //void ImagePreprocess(const cv::Mat &src, EnemyColor enemyColor);

    //static void CropRoi(const cv::Mat &src);
    static void ImagePreprocess(const cv::Mat &src);
    static void CreatTrackbars();
    static void FindLightbar(cv::Mat &preprocessed);
    static void LightBarsPairing();
    static void ClassificationArmor(ArmorStruct& armorStructs);
    static void FilterErrorArmor();
    static void TargetSelection();
    static void DynamicResolutionResize();
    static void DrawReferenceGraphics();

public:
    IdentifyArmor();
    ~IdentifyArmor() {}

    static void IdentifyStream(cv::Mat* pFrame, int* sentData);
};

#endif //ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP
