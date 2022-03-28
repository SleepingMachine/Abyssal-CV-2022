//
// Created by sleepingmachine on 2022/1/9.
//
#ifndef ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP
#define ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP

#include "../asset/RoboMasterConfig.hpp"
#include "../src/serial/serial-port.hpp"
#include "../src/control/control-switch.hpp"
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
    friend class ControlSwitch;

    static void CreatTrackbars();

private:
    static int getFrameErrorCounter;
    static cv::Mat src;
    static cv::Mat searchSrc;
    static cv::Mat srcHSV;
    static cv::Mat maskHSV_0;
    static cv::Mat maskHSV_1;
    static cv::Mat maskHSV;
    static cv::Mat dstHSV;

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

    static double roiRatio_x;
    static double roiRatio_y;
    static double roiScalingRatio_x;
    static double roiScalingRatio_y;

    static bool _cropRoi;
    //static bool _enableRoiScaling;
    static bool _roiScaling;

    static int targetArmorIdex;

    static std::vector<std::vector<cv::Point2i>> allContours;
    static std::vector<cv::Vec4i> hierarchy;
    static std::vector<cv::RotatedRect> filteredLightBars;
    static std::vector<ArmorStruct> armorStructs;
    static cv::Rect lastArmorTarget;
    static cv::Rect2d restoreRect;

    static cv::Point cropOriginPoint;
    static cv::Point lastArmorTargetHitPoint;

    //void ImagePreprocess(const cv::Mat &src, EnemyColor enemyColor);

    //static void CropRoi(const cv::Mat &src);
    static void ImagePreprocess(const cv::Mat &src);

    static void FindLightbar(cv::Mat &preprocessed);
    static void LightBarsPairing();
    static void ClassificationArmor(ArmorStruct& armorStructs);
    static void FilterErrorArmor();
    static void TargetSelection();
    static void DynamicResolutionResize();
    static void DrawReferenceGraphics();

public:
    IdentifyArmor();
    ~IdentifyArmor() {};

    static void ArmorIdentifyStream(cv::Mat importSrc, int* sentData);
};

#endif //ABYSSAL_CV_2022_ARMOR_IDENTIFY_HPP
