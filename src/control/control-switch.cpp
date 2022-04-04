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

void ControlSwitch::SwitchMode(cv::Mat *pFrame, int *sentPortData) {
    cv::Mat temp;
    IdentifyArmor::CreatTrackbars();
    IdentifyEnergyBuff::CreatTrackbars();
    initColorThresholdParameters();

    while(CameraisOpen) {
        if (mutex1.try_lock()) {
            temp = *pFrame;
            mutex1.unlock();
        }
        if (mutex2.try_lock()) {
            *sentPortData = sendData;
            std::cout << *sentPortData << std::endl;
            mutex2.unlock();
        }
        temp.copyTo(src);
        //cv::cvtColor(src, src, cv::COLOR_RGB2BGR);
        //if (src.empty() || (src.cols != 960 || src.rows != 640)) {
        if (src.empty()) {
            std::cout << "Get Frame Fail" << std::endl;
            if (getFrameErrorCounter < 10)
            {
                getFrameErrorCounter++;
                continue;
            }
            else{
                exit(0);
            }
        }
        if (!functionConfig._enableEnergyBuffMode && src.cols == 960 && src.rows == 640){

            src = src(cv::Rect(0,80,960,480));
        }

        //std::cout << sendData << std::endl;

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

void ControlSwitch::initColorThresholdParameters() {

        if(ControlSwitch::functionConfig._enemyColor == EnemyColor::ENEMY_BLUE){
            IdentifyArmor::hmin_0 = 0;
            IdentifyArmor::hmax_0 = 225;
            IdentifyArmor::smin_0 = 0;
            IdentifyArmor::smax_0 = 126;
            IdentifyArmor::vmin_0 = 214;
            IdentifyArmor::vmax_0 = 255;

            IdentifyArmor::hmin_1 = 0;
            IdentifyArmor::hmax_1 = 185;
            IdentifyArmor::smin_1 = 0;
            IdentifyArmor::smax_1 = 174;
            IdentifyArmor::vmin_1 = 141;
            IdentifyArmor::vmax_1 = 255;

            IdentifyEnergyBuff::hmin_0 = 53;
            IdentifyEnergyBuff::hmax_0 = 221;
            IdentifyEnergyBuff::smin_0 = 128;
            IdentifyEnergyBuff::smax_0 = 255;
            IdentifyEnergyBuff::vmin_0 = 98;
            IdentifyEnergyBuff::vmax_0 = 255;

            IdentifyEnergyBuff::hmin_1 = 53;
            IdentifyEnergyBuff::hmax_1 = 148;
            IdentifyEnergyBuff::smin_1 = 128;
            IdentifyEnergyBuff::smax_1 = 255;
            IdentifyEnergyBuff::vmin_1 = 98;
            IdentifyEnergyBuff::vmax_1 = 255;
        }
        else if(ControlSwitch::functionConfig._enemyColor == EnemyColor::ENEMY_RED){
            IdentifyArmor::hmin_0 = 0;
            IdentifyArmor::hmax_0 = 181;
            IdentifyArmor::smin_0 = 0;
            IdentifyArmor::smax_0 = 116;
            IdentifyArmor::vmin_0 = 175;
            IdentifyArmor::vmax_0 = 255;

            IdentifyArmor::hmin_1 = 0;
            IdentifyArmor::hmax_1 = 181;
            IdentifyArmor::smin_1 = 77;
            IdentifyArmor::smax_1 = 255;
            IdentifyArmor::vmin_1 = 205;
            IdentifyArmor::vmax_1 = 255;

            IdentifyEnergyBuff::hmin_0 = 150;
            IdentifyEnergyBuff::hmax_0 = 101;
            IdentifyEnergyBuff::smin_0 = 0;
            IdentifyEnergyBuff::smax_0 = 116;
            IdentifyEnergyBuff::vmin_0 = 175;
            IdentifyEnergyBuff::vmax_0 = 255;

            IdentifyEnergyBuff::hmin_1 = 0;
            IdentifyEnergyBuff::hmax_1 = 138;
            IdentifyEnergyBuff::smin_1 = 74;
            IdentifyEnergyBuff::smax_1 = 255;
            IdentifyEnergyBuff::vmin_1 = 88;
            IdentifyEnergyBuff::vmax_1 = 255;

    }
}
