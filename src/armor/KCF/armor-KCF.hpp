//
// Created by root on 2022/3/10.
//

#ifndef ABYSSAL_CV_2022_ARMOR_KCF_HPP
#define ABYSSAL_CV_2022_ARMOR_KCF_HPP

#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>

#include "../../../asset/RoboMasterConfig.hpp"
#include "../armor-identify.hpp"

class ArmorKCF{
private:
    ArmorKCF();
    ~ArmorKCF() {}
    static void trackerInit(cv::RotatedRect targetArmor, cv::RotatedRect targetArmorLightBar_L, cv::RotatedRect targetArmorLightBar_R);

    static cv::Rect trackingRect;
    static cv::Rect searchingRect;
public:
    static bool _targetArmorFind;
};

#endif //ABYSSAL_CV_2022_ARMOR_KCF_HPP
