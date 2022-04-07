//
// Created by sleepingmachine on 2022/1/9.
//

#ifndef ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP
#define ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP

#include <string>

struct FunctionConfig
{
    //RED => false
    // BLUE => true
    bool _enemyColor                = true;

    bool _enableEnergyBuffMode      = true;

    bool _enableSaveVideo           = false;
    bool _enableRoiScaling          = true;

    bool _enableLocalVideoStreaming = true;
    std::string localVideoPath = "/home/sleepingmachine/视频/lbb_fan.mp4";
    //std::string localVideoPath = "/home/sleepingmachine/视频/lbr_fan.mp4";
    //std::string localVideoPath = "/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/asset/AutoSaveVideo/2022.03.26 14-57-45.avi";


    bool _enableDebugMode           = true;
};

class FunctionConfigFactory{
private:
    static FunctionConfigFactory &instance() {
        static FunctionConfigFactory serialConfigFactory;
        return serialConfigFactory;
    }

public:
    FunctionConfig functionConfig;
    static FunctionConfig getFunctionConfig() {
        return instance().functionConfig;
    }

    static void resetAllConfig() {
        instance().functionConfig = FunctionConfig();
    }
};

//敌方颜色
typedef enum {
    ENEMY_RED = 0,
    ENEMY_BLUE
} EnemyColor;

//我方颜色
typedef enum {
    OWN_RED = 0,
    OWN_BLUE
} OwnColor;

//长短边
enum EXTREMUM {
    SHORT_SIDE = 0,
    LONG_SIDE
};

typedef enum {
    InitMode = 0,
    ArmorMode,
    EnergyBuffMode
} NowMode;

//装甲板参数
struct ArmorPara {
    EnemyColor enemyColor;
    int minLightBarArea = 100;
    int maxLightBarArea = 8000;
    int minLightBarLength = 8;
    int minLightBarWidth = 2;
    int maxLightBarLength = 2000;
    int maxLightBarWidth = 50;
    float minLightBarAspectRatio = 1.5f; //最小长宽比
    float maxLightBarAspectRatio = 10.0f; //最大长宽比
    float maxTwoLightBarsLengthRatio = 1.8f;
    float maxArmorAspectRatio = 4.5f;
    float maxArmorErrorAngle = 20.0f;
    float maxErrorAngle = 15;
    int grayThreshold_PURPLE = 150;
    int grayThreshold_RED = 100;
    int separationThreshold_RED = 80;
    int grayThreshold_BLUE = 160;
    int separationThreshold_BLUE = 80;
    int separationThreshold_GREEN = 10;
    //float reflectionError = 1.1;
    float reflectionErrorWidthThreshold = 1.5;
    float reflectionErrorPositionThreshold = 1.2;
    float detect_thresh = 0.03f;
};

class ArmorParaFactory {
private:
    static ArmorParaFactory &instance() {
        static ArmorParaFactory armorParaFactory;
        return armorParaFactory;
    }

public:
    static ArmorPara getArmorPara() {
        return instance().armorPara;
    }

    static void resetAllConfig() {
        instance().armorPara = ArmorPara();
    }

public:
    ArmorPara armorPara;
};

struct SerialConfig
{
    std::string readPortPath  = "/dev/ttyUSB0";
    std::string writePortPath  = "/dev/ttyUSB1";
    int baud_writePort = 460800;
    int baud_readPort = 460800;
};

class SerialConfigFactory{
private:
    static SerialConfigFactory &instance() {
        static SerialConfigFactory serialConfigFactory;
        return serialConfigFactory;
    }

public:
    SerialConfig serialConfig;
    static SerialConfig getSerialConfig() {
        return instance().serialConfig;
    }

    static void resetAllConfig() {
        instance().serialConfig = SerialConfig();
    }
};

struct EnergyBuffPara {
    EnemyColor enemyColor;
    float minBuffCenterRectArea = 50.0;

};

class EnergyBuffParaFactory {
private:
    static EnergyBuffParaFactory &instance() {
        static EnergyBuffParaFactory energyBuffParaFactory;
        return energyBuffParaFactory;
    }

public:
    static EnergyBuffPara getEnergyBuffPara() {
        return instance().energyBuffPara;
    }

    static void resetAllConfig() {
        instance().energyBuffPara = EnergyBuffPara();
    }
public:
    EnergyBuffPara energyBuffPara;
};
#endif //ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP
