//
// Created by sleepingmachine on 22-4-21.
//

#ifndef ABYSSAL_CV_2022_DECISION_MAKING_HPP
#define ABYSSAL_CV_2022_DECISION_MAKING_HPP

#include "decision-tool.hpp"
#include "../src/control/control-switch.hpp"

#include <stdio.h>
#include <atomic>

#include "opencv2/video/tracking.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/core/cvdef.h"
#include <opencv2/imgproc/imgproc.hpp>

#include <eigen3/Eigen/Dense>

class DecisionMaking{
public:
    static void DecisionStream(int* rawData);


    DecisionMaking();
    ~DecisionMaking();

private:
    static int tempPointData;
    static int lastPointData;

    static int KalmanTracking(int* rawData);
    static void kalmanUpd(bool, float, float);
    static void kalmanPred(bool);

    static int KalmanDemo1(int* rawData);
    static void KalmanDemo2(int* rawData);
};

#endif //ABYSSAL_CV_2022_DECISION_MAKING_HPP
