//
// Created by sleepingmachine on 2022/3/25.
//

#ifndef ABYSSAL_CV_2022_ENERGY_BUFF_HPP
#define ABYSSAL_CV_2022_ENERGY_BUFF_HPP

#include "../asset/RoboMasterConfig.hpp"
#include "../src/serial/serial-port.hpp"
#include "../src/armor/armor-identify.hpp"
#include "../src/energy/energy-tools.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

#include <vector>
#include <iostream>
#include <atomic>
#include <vector>

class IdentifyEnergyBuff{
public:
    IdentifyEnergyBuff();
    ~IdentifyEnergyBuff() {};
    friend class ControlSwitch;

    static void EnergyBuffIdentifyStream(cv::Mat importSrc, int* sentData);
    static void CreatTrackbars();
private:
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

    static cv::Point_<float> rLogoRectCenterPoint;
    static cv::Point hitPoint;

    static cv::RotatedRect rLogoRect;

    static std::vector<std::vector<cv::Point2i> > allContours;
    static std::vector<cv::Vec4i> hierarchy;

    static std::vector<cv::RotatedRect> possibleBladeRects;
    static std::vector<cv::RotatedRect> possibleRLogoRects;

    static std::vector<cv::RotatedRect> bladeRects;
    static std::vector<cv::RotatedRect> bladeInlineRects;
    static std::vector<cv::RotatedRect> bladeArmorRects;

    static std::vector<float> possibleBladeRectsArea;
    static std::vector<int> possibleBladeRectParentProfiles;
    static std::vector<int> possibleBladeRectChildProfiles;

    static float rLogoRectLongSide;
    static float rLogoRectArea;

    static cv::Mat src;
    static cv::Mat searchSrc;
    static cv::Mat srcHSV;
    static cv::Mat maskHSV;
    static cv::Mat maskHSV_0;
    static cv::Mat maskHSV_1;
    static cv::Mat dstHSV;

    static bool _findEnergyBuffTarget;
    static bool _cropRoi;

    static cv::Point cropOriginPoint;

    static void ImagePreprocess(const cv::Mat &src);
    static void searchContours_PossibleRect();
    static void searchContours_BuffCenter(std::vector<cv::RotatedRect> possibleRLogoRects);
    static void searchContours_Cantilever(std::vector<cv::RotatedRect> possibleBladeRects);
    static void resourceRelease();
    static bool circleCenterSVM(cv::RotatedRect &inputRect);
    static void DynamicResolutionResize();
    static void DrawReferenceGraphics();
    static void HitBladePairing();

    static cv::Ptr<cv::ml::SVM> rLogoCenterSVM;
};
#endif //ABYSSAL_CV_2022_ENERGY_BUFF_HPP
