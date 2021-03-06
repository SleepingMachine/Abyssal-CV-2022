//
// Created by sleepingmachine on 2022/1/9.
//

#ifndef ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP
#define ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP

#include <string>

struct FunctionConfig
{
    // RED  => false
    // BLUE => true
    bool _enemyColor                  = true;
    // HSV => false
    // RGB => true
    bool _colorSpace                  = true;

    bool _enableEnergyBuffMode        = false;

    bool _enableSaveVideo             = false;
    bool _enableRoiScaling            = true;
    bool _enableArmorKCF              = false;

    // 0   => false
    // 180 => true
    bool  _imageOrientationCorrection = true;
    bool _enableLocalVideoStreaming   = false;
    bool _enableUsbCamera             = false;

    std::string localVideoPath = "/home/sleepingmachine/视频/lbb_fan.mp4";
    //std::string localVideoPath = "/home/sleepingmachine/视频/lbr_fan.mp4";
    //std::string localVideoPath = "/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/asset/AutoSaveVideo/2022.05.01 23-01-38.avi";
    
    bool _enableDebugMode             = true;
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
    float maxArmorErrorAngle = 50.0f;
    float maxErrorAngle = 15;
    int grayThreshold_PURPLE = 150;
    int grayThreshold_RED = 80;
    int separationThreshold_RED = 50;
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
    float maxBuffCenterRectArea = 450.0;

    float maxBuffCenterRectAspectRatio = 1.5;

    float minBuffBladeRectsAreaRatio = 20;
    float maxBuffBladeRectsAreaRatio = 50;
    float minBuffBladeRectsAspectRatio = 1.5;
    float maxBuffBladeRectsAspectRatio = 3;

    float minBuffBladeInlineRectsAreaRatio = 4;
    float maxBuffBladeInlineRectsAreaRatio = 10;
    float minBuffBladeInlineRectsAspectRatio = 3;
    float maxBuffBladeInlineRectsAspectRatio = 10;

    float minBuffBladeArmorRectsAreaRatio = 2;
    float maxBuffBladeArmorRectsAreaRatio = 6;
    float minBuffBladeArmorRectsAspectRatio = 1;
    float maxBuffBladeArmorRectsAspectRatio = 3;

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
