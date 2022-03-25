//
// Created by sleepingmachine on 2022/2/21.
//
#include "video-save.hpp"

extern std::mutex mutex1;
extern std::atomic_bool CameraisOpen;

static FunctionConfig functionConfig = FunctionConfigFactory::getFunctionConfig();

cv::Mat VideoSave::src(480, 960, CV_8UC3);
cv::Mat VideoSave::temp(480, 960, CV_8UC3);

//bool Temp_AutoSaveVideo = true; //TODO:修改一个更加安全的控件

void VideoSave::SaveRunningVideo(cv::Mat *pFrame) {
    if (functionConfig._enableSaveVideo){
        time_t timep;
        char name[256] = {0};

        time(&timep);//获取从1970至今过了多少秒，存入time_t类型的timep

        strftime( name, sizeof(name), "../asset/AutoSaveVideo/%Y.%m.%d %H-%M-%S.avi",localtime(&timep) ); //最后一个参数是用localtime将秒数转化为struct tm结构体

        std::string outputVideoPath = name;
        cv::VideoWriter outputVideo;
        outputVideo.open(outputVideoPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 60.0, cv::Size(640, 480), true);
        while(CameraisOpen) {
            if (mutex1.try_lock()) {
                temp = *pFrame;
                mutex1.unlock();
            }
            temp.copyTo(src);
            if (src.empty()) {
                std::cout << "Get Save Video Frame Fail" << std::endl;
                break;
            }

            cv::Mat output;
            //cv::Mat roi;
            //roi = src(cv::Rect(cv::Point(160,0),cv::Point(800,480)));
            //output = roi.clone();
            cv::resize(src,output,cv::Size(640,480));
            outputVideo << output;
            //cv::imshow("Output", output);
            cv::waitKey(1);
        }
    }

}
