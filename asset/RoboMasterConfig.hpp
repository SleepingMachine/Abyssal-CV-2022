//
// Created by sleepingmachine on 2022/1/9.
//

#ifndef ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP
#define ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP

#include <string>

struct FunctionConfig
{
    bool _enableEnergyBuffMode      = false;

    bool _enableSaveVideo           = true;
    bool _enableRoiScaling          = true;

    bool _enableLocalVideoStreaming = false;
    std::string localVideoPath = "/home/sleepingmachine/RoboMaster-Code/Abyssal-CV@2022/asset/AutoSaveVideo/2022.03.26 14-57-45.avi";
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
    int minLightBarArea = 300;
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
    float reflectionError = 1.1;
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
/*
    static void readArmorPara(const std::string &filename) {
        cv::FileStorage fs(filename, cv::FileStorage::READ);
        if (!fs.isOpened()) {
            writeArmorPara(filename);
            LOG::error("default config not find, write config to " + filename);
        } else {
            // 读入普通节点
            //读入map类型的节点
            cv::FileNode map_node = fs["armorPara"];
            map_node["minLightBarArea"] >> instance().armorPara.minLightBarArea;
            map_node["minLightBarLength"] >> instance().armorPara.minLightBarLength;
            map_node["minLightBarWidth"] >> instance().armorPara.minLightBarWidth;
            map_node["maxLightBarLength"] >> instance().armorPara.maxLightBarLength;
            map_node["maxLightBarWidth"] >> instance().armorPara.maxLightBarWidth;
            map_node["maxErrorAngle"] >> instance().armorPara.maxErrorAngle;
            map_node["grayThreshold_PURPLE"] >> instance().armorPara.grayThreshold_PURPLE;
            map_node["grayThreshold_RED"] >> instance().armorPara.grayThreshold_RED;
            map_node["separationThreshold_RED"] >> instance().armorPara.separationThreshold_RED;
            map_node["grayThreshold_BLUE"] >> instance().armorPara.grayThreshold_BLUE;
            map_node["separationThreshold_BLUE"] >> instance().armorPara.separationThreshold_BLUE;
            map_node["separationThreshold_GREEN"] >> instance().armorPara.separationThreshold_GREEN;
            LOG::debug("armorPara.minLightBarArea=" + std::to_string(instance().armorPara.minLightBarArea));
            LOG::debug("armorPara.minLightBarLength=" + std::to_string(instance().armorPara.minLightBarLength));
            LOG::debug("armorPara.minLightBarWidth=" + std::to_string(instance().armorPara.minLightBarWidth));
            LOG::debug("armorPara.maxLightBarLength=" + std::to_string(instance().armorPara.maxLightBarLength));
            LOG::debug("armorPara.maxLightBarWidth=" + std::to_string(instance().armorPara.maxLightBarWidth));
            LOG::debug("armorPara.maxErrorAngle=" + std::to_string(instance().armorPara.maxErrorAngle));
            LOG::debug("armorPara.grayThreshold_PURPLE=" + std::to_string(instance().armorPara.grayThreshold_PURPLE));
            LOG::debug("armorPara.grayThreshold_RED=" + std::to_string(instance().armorPara.grayThreshold_RED));
            LOG::debug("armorPara.separationThreshold_RED=" + std::to_string(instance().armorPara.separationThreshold_RED));
            LOG::debug("armorPara.grayThreshold_BLUE=" + std::to_string(instance().armorPara.grayThreshold_BLUE));
            LOG::debug("armorPara.separationThreshold_BLUE=" + std::to_string(instance().armorPara.separationThreshold_BLUE));
            LOG::debug("armorPara.separationThreshold_GREEN=" + std::to_string(instance().armorPara.separationThreshold_GREEN));
        }
    }

    static void writeArmorPara(const std::string &filename) {
        cv::FileStorage fs(filename, cv::FileStorage::WRITE);

        fs.writeComment("装甲板识别数据");
        fs << "armorPara" << "{";
        fs.writeComment("最小的灯条面积");
        fs << "minLightBarArea" << instance().armorPara.minLightBarArea;
        fs.writeComment("最小的灯条长度");
        fs << "minLightBarLength" << instance().armorPara.minLightBarLength;
        fs.writeComment("最小的灯条宽度");
        fs << "minLightBarWidth" << instance().armorPara.minLightBarWidth;
        fs.writeComment("最大灯条长度");
        fs << "maxLightBarLength" << instance().armorPara.maxLightBarLength;
        fs.writeComment("最大灯条宽度");
        fs << "maxLightBarWidth" << instance().armorPara.maxLightBarWidth;
        fs.writeComment("容许的最大角度差");
        fs << "maxErrorAngle" << instance().armorPara.maxErrorAngle;
        fs.writeComment("灰度二值化阈值-紫色");
        fs << "grayThreshold_PURPLE" << instance().armorPara.grayThreshold_PURPLE;
        fs.writeComment("灰度二值化阈值-红色");
        fs << "grayThreshold_RED" << instance().armorPara.grayThreshold_RED;
        fs.writeComment("色彩分离二值化阈值-红色");
        fs << "separationThreshold_RED" << instance().armorPara.separationThreshold_RED;
        fs.writeComment("灰度二值化阈值-蓝色");
        fs << "grayThreshold_BLUE" << instance().armorPara.grayThreshold_BLUE;
        fs.writeComment("色彩分离二值化阈值-蓝色");
        fs << "separationThreshold_BLUE" << instance().armorPara.separationThreshold_BLUE;
        fs.writeComment("色彩分离二值化阈值-绿色");
        fs << "separationThreshold_GREEN" << instance().armorPara.separationThreshold_GREEN;
        fs << "}";
        //销毁
        fs.release();
    }
*/
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

#endif //ABYSSAL_CV_2022_ROBOMASTERDEFINE_HPP
