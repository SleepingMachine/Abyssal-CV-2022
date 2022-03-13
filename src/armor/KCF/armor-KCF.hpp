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
    //static int lostTrackTarget = 0;
    static bool trackerSuccess;
    static bool firstLoad;
    //static bool _isTrackerStart = false;
    static int srcWidth;
    static int srcHeight;
    static cv::Size _size;
    static cv::RotatedRect resultRect;
    static cv::RotatedRect resLast;
    static cv::Rect restoreRect;
    static cv::Point2f vertices[4];

public:
    static void trackerInit(const cv::Mat &src, EnemyColor enemyColor);
    static void trackerStart(cv::RotatedRect, cv::RotatedRect, cv::RotatedRect);
    static void trackerCallBack(cv::Mat);

    static bool trackingInProgress;
    static bool findReulst;
    cv::RotatedRect _resLast;
    static cv::Rect trackerRect;
    static cv::Rect searchRect;
    static cv::Mat trackingSrc;
    ArmorKCF();
    ~ArmorKCF() {}


};
#endif //ABYSSAL_CV_2022_ARMOR_KCF_HPP
