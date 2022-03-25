//
// Created by sleepingmachine on 2022/2/21.
//

#ifndef ABYSSAL_CV_2022_VIDEO_SAVE_HPP
#define ABYSSAL_CV_2022_VIDEO_SAVE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <atomic>
#include <stdio.h>
#include <time.h>

#include "../asset/RoboMasterConfig.hpp"

class VideoSave{
public:
    static void SaveRunningVideo(cv::Mat* pFrame);

private:
    static cv::Mat temp;
    static cv::Mat src;
};

#endif //ABYSSAL_CV_2022_VIDEO_SAVE_HPP
