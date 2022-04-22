//
// Created by sleepingmachine on 22-4-21.
//

#ifndef ABYSSAL_CV_2022_DECISION_MAKING_HPP
#define ABYSSAL_CV_2022_DECISION_MAKING_HPP

#include "decision-tool.hpp"
#include "../src/control/control-switch.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/cvdef.h"
#include <stdio.h>
#include <atomic>

class DecisionMaking{
public:
    static void DecisionStream(int* rawData);


    DecisionMaking();
    ~DecisionMaking();

private:
    static int tempPointData;
    static int lastPointData;
    static int KalmanDemo(int* rawData);
};

#endif //ABYSSAL_CV_2022_DECISION_MAKING_HPP
