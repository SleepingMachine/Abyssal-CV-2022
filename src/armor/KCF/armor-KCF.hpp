//
// Created by root on 2022/3/10.
//

#ifndef ABYSSAL_CV_2022_ARMOR_KCF_HPP
#define ABYSSAL_CV_2022_ARMOR_KCF_HPP

#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>

#include "../../../asset/RoboMasterConfig.hpp"
#include "../armor-identify.hpp"
#include <stdio.h>
#include <atomic>

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/core/cvdef.h"
#include <opencv2/imgproc/imgproc.hpp>

#include <eigen3/Eigen/Dense>

class ArmorKCF{
private:
    ArmorKCF();
    ~ArmorKCF() {}
    static void kalmanUpd(bool, float, float);
    static void kalmanPred(bool);
public:
    //static int KalmanTracking(int* rawData);
    static bool _targetArmorFind;
    static bool start;
};

#endif //ABYSSAL_CV_2022_ARMOR_KCF_HPP
