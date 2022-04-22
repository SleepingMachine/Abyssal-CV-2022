//
// Created by sleepingmachine on 22-4-21.
//

#ifndef ABYSSAL_CV_2022_DECISION_TOOL_HPP
#define ABYSSAL_CV_2022_DECISION_TOOL_HPP

#include <opencv2/core/types.hpp>

static inline cv::Point calcPoint(cv::Point2f center, double R, double angle)
{
    return center + cv::Point2f((float)cos(angle), (float)-sin(angle))*(float)R;
}

#endif //ABYSSAL_CV_2022_DECISION_TOOL_HPP
