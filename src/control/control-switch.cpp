//
// Created by sleepingmachine on 2022/3/25.
//

#include "control-switch.hpp"

extern std::atomic_bool CameraisOpen;

extern std::mutex mutex1;
extern std::mutex mutex2;

FunctionConfig ControlSwitch::functionConfig = FunctionConfigFactory::getFunctionConfig();

ControlSwitch::ControlSwitch() {}

int ControlSwitch::sendData = 0;
int ControlSwitch::lastMode = NowMode::InitMode;
int ControlSwitch::getFrameErrorCounter = 0;

cv::Mat ControlSwitch::src(480, 960, CV_8UC3);

void ControlSwitch::SwitchMode(cv::Mat *pFrame) {
    IdentifyArmor::CreatTrackbars();
    cv::Mat temp;
    while(CameraisOpen) {
        if (mutex1.try_lock()) {
            temp = *pFrame;
            mutex1.unlock();
        }
        temp.copyTo(src);
        //cv::cvtColor(src, src, cv::COLOR_RGB2BGR);
        if (src.empty()) {
            std::cout << "Get Frame Fail" << std::endl;
            if (getFrameErrorCounter < 3)
            {
                continue;
            }
            else{
                exit(0);
            }
        }
        if (!functionConfig._enableEnergyBuffMode){
            src = src(cv::Rect(0,80,960,480));
        }

        /*
        if ((!functionConfig._enableEnergyBuffMode && lastMode == NowMode::InitMode) || (!functionConfig._enableEnergyBuffMode && lastMode == NowMode::ArmorMode)){
            lastMode = NowMode::ArmorMode;
            IdentifyArmor::ArmorIdentifyStream(src, &sendData);
        }
        else if ((functionConfig._enableEnergyBuffMode && lastMode == NowMode::InitMode) || (functionConfig._enableEnergyBuffMode && lastMode == NowMode::EnergyBuffMode)){
            lastMode = NowMode::EnergyBuffMode;
        }
        else if (!functionConfig._enableEnergyBuffMode && lastMode == NowMode::EnergyBuffMode){
            lastMode = NowMode::ArmorMode;
        }
        else if (functionConfig._enableEnergyBuffMode && lastMode == NowMode::ArmorMode){
            lastMode = NowMode::EnergyBuffMode;
        }*/
        int c = cv::waitKey(5);
        if (c == 'e') {
            functionConfig._enableEnergyBuffMode = !functionConfig._enableEnergyBuffMode;
        }
        if (!functionConfig._enableEnergyBuffMode){
            lastMode = NowMode::ArmorMode;
            IdentifyArmor::ArmorIdentifyStream(src, &sendData);
        }
        else if (functionConfig._enableEnergyBuffMode){
            lastMode = NowMode::EnergyBuffMode;
            IdentifyEnergyBuff::EnergyBuffIdentifyStream(src, &sendData);
        }
    }
}
