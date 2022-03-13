//
// Created by root on 2022/3/10.
//

#ifndef ABYSSAL_CV_2022_ARMOR_KCF_HPP
#define ABYSSAL_CV_2022_ARMOR_KCF_HPP

#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>

#include "../../../asset/RoboMasterConfig.hpp"
#include "../armor-identify.hpp"

//#include <opencv2/tracking/tracker.hpp>
class ArmorKCF{
private:
    static cv::Ptr<cv::TrackerKCF> trackerKCF;
    static cv::TrackerKCF::Params _params;
    static bool trackerFindTarget;
    static bool firstLoad;
    //static bool _isTrackerStart = false;
    static int srcWidth;
    static int srcHeight;
    static cv::Size _size;
    static cv::RotatedRect resultRect;
    static cv::RotatedRect resLast;
    static cv::Rect restoreRect;
    static cv::Point2f vertices[4];
    static cv::Rect trackingRect;
    static cv::Rect searchingRect;
    static bool trackerInit;

public:
    //static void trackerInit(const cv::Mat &src, EnemyColor enemyColor);
    //static void trackerStart(cv::RotatedRect, cv::RotatedRect, cv::RotatedRect);

    static void trackerUpdate(const cv::Mat &src);
    static void trackingStart(cv::RotatedRect targetArmor, cv::RotatedRect targetArmorLightBar_L, cv::RotatedRect targetArmorLightBar_R);
    static void trackerCallBack(cv::Mat);
    static bool trackingInProgress;
    static bool findReulst;
    cv::RotatedRect _resLast;
    static cv::Mat searchingSrc;
    ArmorKCF();
    ~ArmorKCF() {}

    static bool trackerIsReady;
//static int lostTrackTarget = 0;
static bool trackerSuccess;
};
#endif //ABYSSAL_CV_2022_ARMOR_KCF_HPP
