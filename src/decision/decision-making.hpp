//
// Created by sleepingmachine on 22-4-21.
//

#ifndef ABYSSAL_CV_2022_DECISION_MAKING_HPP
#define ABYSSAL_CV_2022_DECISION_MAKING_HPP

#include "decision-tool.hpp"
#include "../src/control/control-switch.hpp"
#include "opencv2/video/tracking.hpp"
#include <opencv2/highgui/highgui_c.h>
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
    static void mouseEvent(int event, int x, int y, int flags, void *param );
    static int lastPointData;
    static int KalmanDemo(int* rawData);
    static void KalmanDemo2(int* rawData);
};

#endif //ABYSSAL_CV_2022_DECISION_MAKING_HPP
