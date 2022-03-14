//
// Created by sleepingmachine on 2022/1/9.
//
#include "armor-identify.hpp"
#include "../asset/RoboMasterConfig.hpp"

extern std::mutex mutex1;
extern std::mutex mutex2;
extern std::atomic_bool CameraisOpen;

int IdentifyArmor::getFrameErrorCounter = 0;

//默认hsv颜色阈值
int IdentifyArmor::hmin = 63;
int IdentifyArmor::hmax = 255;
int IdentifyArmor::smin = 0;
int IdentifyArmor::smax = 255;
int IdentifyArmor::vmin = 235;
int IdentifyArmor::vmax = 255;

//默认二值化操作阈值
int IdentifyArmor::open = 1;
int IdentifyArmor::cclose = 18;
int IdentifyArmor::erode = 3;
int IdentifyArmor::dilate = 12;

int IdentifyArmor::targetArmorIdex = 0;

std::vector<std::vector<cv::Point2i>> IdentifyArmor::allContours;
std::vector<cv::Vec4i> IdentifyArmor::hierarchy;
std::vector<cv::RotatedRect> IdentifyArmor::filteredLightBars;
std::vector<IdentifyArmor::ArmorStruct> IdentifyArmor::armorStructs;

static ArmorPara armorPara = ArmorParaFactory::getArmorPara();

cv::Rect IdentifyArmor::lastArmorTarget;
cv::Rect2d IdentifyArmor::restoreRect;

bool ArmorKCF::_targetArmorFind= false;
bool IdentifyArmor::_cropRoi = false;

cv::Mat IdentifyArmor::src(640, 1280, CV_8UC3);
cv::Mat IdentifyArmor::srcHSV(640, 1280, CV_8UC3);
cv::Mat IdentifyArmor::maskHSV(640, 1280, CV_8UC3);
cv::Mat IdentifyArmor::dstHSV(640, 1280, CV_8UC3);

cv::Mat IdentifyArmor::searchSrc(640, 1280, CV_8UC3);
cv::Point IdentifyArmor::cropOriginPoint = cv::Point(0,0);

IdentifyArmor::IdentifyArmor() {}

void IdentifyArmor::IdentifyStream(cv::Mat *pFrame, int* sentData) {
//#if DEBUG
    CreatTrackbars();
//#endif
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
//        std::cout << 1111 << std::endl;
        //CropRoi(src);
        ImagePreprocess(src);
        FindLightbar(dstHSV);
        LightBarsPairing();
        FilterErrorArmor();
        TargetSelection();

        for(int i = 0; i < armorStructs.size(); i++){
            ArmorTool::drawRotatedRect(src, armorStructs[i].armorRect, cv::Scalar(0, 165, 255), 2, 16);
            cv::circle(src, armorStructs[i].hitPoint, 1, cv::Scalar(0, 165, 255), 4);  // 画半径为1的圆(画点）
            //cv::circle(src, cropOriginPoint, 3, cv::Scalar(0, 165, 255), 4);  // 画半径为1的圆(画点）
        }//绘制矩形
        /*
        if(ArmorKCF::findReulst) {
            ArmorKCF::trackerStart(armorStructs[targetArmorIdex].armorRect,armorStructs[targetArmorIdex].partLightBars[0],armorStructs[targetArmorIdex].partLightBars[1]);
        }*/
        //TestDemo
        if(armorStructs.size() > 0){
            int hitPointx = armorStructs[targetArmorIdex].hitPoint.x;
            int hitPointy = armorStructs[targetArmorIdex].hitPoint.y;
            int hitPointData = hitPointx * 1000 + hitPointy;

            if (mutex2.try_lock()) {
                *sentData = hitPointData;
                mutex2.unlock();
            }
            //SerialPort::getHitPointData(hitPointx,hitPointy);
        }

        allContours.clear();                                //轮廓
        hierarchy.clear();
        filteredLightBars.clear();
        armorStructs.clear();

        //cv::imshow("mask", maskHSV);
        cv::imshow("Preprocessed Dst", dstHSV);
        cv::imshow("Src", src);
        cv::waitKey(5);
    }
}

void IdentifyArmor::CreatTrackbars() {
    cv::namedWindow("阈值调整",cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("hmin", "阈值调整",&IdentifyArmor::hmin, 255,NULL);
    cv::createTrackbar("hmax", "阈值调整",&IdentifyArmor::hmax, 255,NULL);
    cv::createTrackbar("smin", "阈值调整",&IdentifyArmor::smin, 255,NULL);
    cv::createTrackbar("smax", "阈值调整",&IdentifyArmor::smax, 255,NULL);
    cv::createTrackbar("vmin", "阈值调整",&IdentifyArmor::vmin, 255,NULL);
    cv::createTrackbar("vmax", "阈值调整",&IdentifyArmor::vmax, 255,NULL);
    cv::createTrackbar("open", "阈值调整",&IdentifyArmor::open, 10,NULL);
    cv::createTrackbar("close", "阈值调整",&IdentifyArmor::cclose, 30,NULL);
    cv::createTrackbar("erode", "阈值调整",&IdentifyArmor::erode, 10,NULL);
    cv::createTrackbar("dilate", "阈值调整",&IdentifyArmor::dilate, 20,NULL);
}

void IdentifyArmor::FindLightbar(cv::Mat &preprocessedImage) {
    cv::findContours(preprocessedImage, IdentifyArmor::allContours, IdentifyArmor::hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < IdentifyArmor::allContours.size(); ++i) {
        if (IdentifyArmor::hierarchy[i][3] == -1) {
            cv::RotatedRect scanRect = cv::minAreaRect(IdentifyArmor::allContours[i]);                    //检测最小面积的矩形

            cv::Point2f vertices[4];
            scanRect.points(vertices);
            //std::cout << ArmorTool::getRectLengthWidthRatio(scanRect) << std::endl;
            cv::circle(src, cv::Point(vertices[0].x,vertices[0].y), 1, cv::Scalar(255, 255, 0), 2);  // 画半径为1的圆(画点）
            cv::circle(src, cv::Point(vertices[1].x,vertices[1].y), 1, cv::Scalar(255, 0, 255), 2);  // 画半径为1的圆(画点）
            cv::circle(src, cv::Point(vertices[2].x,vertices[2].y), 1, cv::Scalar(20, 243, 32), 2);  // 画半径为1的圆(画点）
            cv::circle(src, cv::Point(vertices[3].x,vertices[3].y), 1, cv::Scalar(255, 0, 0), 2);  // 画半径为1的圆(画点）
            cv::circle(src, cv::Point(vertices[4].x,vertices[4].y), 1, cv::Scalar(	0, 255, 255), 2);  // 画半径为1的圆(画点）


            //std::cout << "sfhdiwuda" << fabs(vertices[0].y - vertices[2].y) / fabs(vertices[0].x - vertices[2].x) << std::endl;

            if(fabs(ArmorTool::getTwoPointDistance(vertices[1], vertices[0])) >= fabs(ArmorTool::getTwoPointDistance(vertices[1], vertices[2])))
            {
                if (ArmorTool::getTwoPointDistance(vertices[1], vertices[0]) / ArmorTool::getTwoPointDistance(vertices[1], vertices[2]) < ::armorPara.minLightBarAspectRatio || ArmorTool::getTwoPointDistance(vertices[1], vertices[0]) / ArmorTool::getTwoPointDistance(vertices[1], vertices[2]) > ::armorPara.maxLightBarAspectRatio)
                {
                    continue;
                }

            }
            else{ if (ArmorTool::getTwoPointDistance(vertices[1], vertices[2]) / ArmorTool::getTwoPointDistance(vertices[1], vertices[0]) < ::armorPara.minLightBarAspectRatio || ArmorTool::getTwoPointDistance(vertices[1], vertices[2]) / ArmorTool::getTwoPointDistance(vertices[1], vertices[0]) > ::armorPara.maxLightBarAspectRatio)
                {
                    continue;
                }

            }
            if(scanRect.size.area() < ::armorPara.minLightBarArea || scanRect.size.area() > ::armorPara.maxLightBarArea)
            {
                continue;
            }

            float longSide = ArmorTool::findExtremumOfSide(scanRect, LONG_SIDE);
            float shortSide = ArmorTool::findExtremumOfSide(scanRect, SHORT_SIDE);
            if (longSide > ::armorPara.maxLightBarLength || longSide < ::armorPara.minLightBarLength || shortSide > ::armorPara.maxLightBarWidth || shortSide < ::armorPara.minLightBarWidth)
                continue;

            filteredLightBars.push_back(scanRect);
            /*
            for (int j = 0; j < 4; j++)
            {
                cv::line(src, vertices[j], vertices[(j + 1) % 4], cv::Scalar(219,112,147),1);
            }
            */
            //std::cout << "scanRect.size.area():" << scanRect.size.area() << std::endl;

            /*
            //rect的高度、和宽度有一个小于板灯的最小高度就直接跳过本次循环
            float longSide = Util::findExtremumOfSide(scanRect, LONG_SIDE);
            float shortSide = Util::findExtremumOfSide(scanRect, SHORT_SIDE);
            //std::cout << "longSide:" << longSide << std::endl;
            //std::cout << "shortSide:" << shortSide << std::endl;
            if (longSide > _para.maxLightBarLength || longSide < _para.minLightBarLength || shortSide > _para.maxLightBarWidth || shortSide < _para.minLightBarWidth)
                continue;

            if (longSide > shortSide * 8.0f || longSide < shortSide * 1.5f)
                continue;

            possibleRects.push_back(scanRect);
            //std::cout << "*" << std::endl;*/
        }
    }

    //std::cout << filteredLightBars.size() << std::endl;

    for (int i = 0; i < filteredLightBars.size(); ++i) {
        for (int j = i+1; j < filteredLightBars.size(); ++j) {
            //std::cout << filteredLightBars[i].size.area() << std::endl;
            //ArmorTool::drawRotatedRect(src, filteredLightBars[i], cv::Scalar(0, 0, 0), 2, 16);
            //ArmorTool::drawRotatedRect(src, filteredLightBars[j], cv::Scalar(255,255,255), 2, 16);
            if(filteredLightBars[i].size.area() >= filteredLightBars[j].size.area()){
                if((abs(filteredLightBars[j].center.x - filteredLightBars[i].center.x) < filteredLightBars[i].size.width/2) && (abs(filteredLightBars[j].center.y - filteredLightBars[i].center.y) < filteredLightBars[i].size.height/2)){
                    filteredLightBars.erase(std::begin(filteredLightBars) + j);
                }
            }
            if(filteredLightBars[j].size.area() > filteredLightBars[i].size.area()){
                if((abs(filteredLightBars[j].center.x - filteredLightBars[i].center.x) < filteredLightBars[j].size.width/2) && (abs(filteredLightBars[j].center.y - filteredLightBars[i].center.y) < filteredLightBars[j].size.height/2)){
                    filteredLightBars.erase(std::begin(filteredLightBars) + i);
                }
            }
        }
    }

    // std::cout << filteredLightBars.size() << std::endl;
    for (int i = 0; i < filteredLightBars.size(); ++i) {
        ArmorTool::drawRotatedRect(src, filteredLightBars[i], cv::Scalar(15, 198, 150), 1, 16);
    }
}

void IdentifyArmor::ImagePreprocess(const cv::Mat &src) {
    /*
    const cv::Point& lastArmorTargetCenter = lastArmorTarget.center;
    if (lastArmorTarget.size.empty()){

        restoreRect = cv::Rect(0, 0, src.cols, src.rows);
        IdentifyArmor::src(restoreRect).copyTo(searchSrc);
        //searchSrc = src;                                                        //继承原图片地址
        _cropRoi = false;
    }
    else if (!lastArmorTarget.size.empty()){
        cv::Rect rect = lastArmorTarget.boundingRect();                            //返回包含旋转矩形的最小右上整数矩形。
        static float ratioToWidth = 2.0f;
        static float ratioToHeight = 3.0f;
        int x1 = MAX(int(lastArmorTargetCenter.x - (rect.width * ratioToWidth)), 0);
        int y1 = MAX(int(lastArmorTargetCenter.y - (rect.height * ratioToHeight)), 0);
        cv::Point lu = cv::Point(x1, y1);                                                           //得到点lu，ROI左上角的起点
        cropOriginPoint = lu;
        int x2 = MIN(int(lastArmorTargetCenter.x + (rect.width * ratioToWidth)), src.cols);                //计算结果不大于图片长宽
        int y2 = MIN(int(lastArmorTargetCenter.y + (rect.height * ratioToHeight)), src.rows);
        cv::Point rd = cv::Point(x2, y2);                                                           //得到点rd，ROI右下角的终点
        restoreRect = cv::Rect(lu, rd);
        rectangle(src,restoreRect, cv::Scalar(0, 255, 255));

        src(restoreRect).copyTo(searchSrc);
        _cropRoi = true;
        cv::imshow("12", searchSrc);
    }
     */
    cv::cvtColor(src, srcHSV, CV_BGR2HSV, 0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyArmor::hmin, IdentifyArmor::smin, IdentifyArmor::vmin), cv::Scalar(IdentifyArmor::hmax, IdentifyArmor::smax, IdentifyArmor::vmax), maskHSV);
    //cv::inRange(srcHSV, cv::Scalar(40,120,230), cv::Scalar(80, 120, 255), maskHSV);
    morphologyEx(maskHSV, dstHSV, 2, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyArmor::open,IdentifyArmor::open)));
    morphologyEx(dstHSV, dstHSV, 3, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyArmor::cclose,IdentifyArmor::cclose)));
    morphologyEx(dstHSV, dstHSV, 0, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyArmor::erode,IdentifyArmor::erode)));
    morphologyEx(dstHSV, dstHSV, 1, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyArmor::dilate,IdentifyArmor::dilate)));
}

/*
float IdentifyArmor::getTwoPointDistance(cv::Point2f point_1, cv::Point2f point_2) {
    return sqrtf(pow((point_1.x - point_2.x), 2) + pow((point_1.y - point_2.y), 2));
}*/

void IdentifyArmor::LightBarsPairing() {
    ArmorStruct armorStruct;

    //std::cout << filteredLightBars.size() << std::endl;
    if (filteredLightBars.size() < 2) {
        return;
    }

    cv::Point2f shortCenter0[2];
    cv::Point2f shortCenter1[2];
    for (int i = 0; i < filteredLightBars.size()-1; ++i) {
        for(int j = i+1; j < filteredLightBars.size();j++){
            float rectLength_0 = 0, rectLength_1 = 0, longerRectLength = 0, shorterRectLength = 0;
            float distanceBetweenTwoRect;
            rectLength_0 = ArmorTool::findExtremumOfSide(filteredLightBars[i], LONG_SIDE);
            rectLength_1 = ArmorTool::findExtremumOfSide(filteredLightBars[j], LONG_SIDE);
            if(rectLength_0 >= rectLength_1){
                longerRectLength = rectLength_0;
                shorterRectLength = rectLength_1;
            }
            else{
                longerRectLength = rectLength_1;
                shorterRectLength = rectLength_0;
            }
            
            if (fabs(filteredLightBars[i].center.x - filteredLightBars[j].center.x) > longerRectLength * 0.8f ||
                fabs(filteredLightBars[i].center.y - filteredLightBars[j].center.y) > shorterRectLength * 0.3f) {
                float twoRectLengthRatio = rectLength_0 > rectLength_1 ? (rectLength_0 / rectLength_1) : (rectLength_1 / rectLength_0);
                if (twoRectLengthRatio < ::armorPara.maxTwoLightBarsLengthRatio){
                    //std::cout << twoRectLengthRatio << std::endl;
                    distanceBetweenTwoRect = ArmorTool::getTwoPointDistance(filteredLightBars[i].center, filteredLightBars[j].center);
                    //cv::line(src,filteredLightBars[i].center, filteredLightBars[j].center,cv::Scalar(255,255,255));

                    if (distanceBetweenTwoRect < longerRectLength * ::armorPara.maxArmorAspectRatio) {
                        ArmorTool::getShortCenter(filteredLightBars[i], shortCenter0);
                        ArmorTool::getShortCenter(filteredLightBars[j], shortCenter1);

                        float lightBarsAngle = ArmorTool::lineToLineAngle(shortCenter0[0], shortCenter0[1], shortCenter1[0], shortCenter1[1]);

                        if ((ArmorTool::getLightBarTan(filteredLightBars[i]) * ArmorTool::getLightBarTan(filteredLightBars[j]) < 0.0f) || lightBarsAngle > 13.0f){
                            continue;
                        }
                        if (ArmorTool::calSkewingAngle(filteredLightBars[i], filteredLightBars[j], shortCenter0) < 75.0f || ArmorTool::calSkewingAngle(filteredLightBars[i], filteredLightBars[j], shortCenter1) < 75.0f)
                            continue;
                        //cv::line(src,filteredLightBars[i].center, filteredLightBars[j].center,cv::Scalar(255,255,255));

                        cv::RotatedRect armor = ArmorTool::assembleArmor(filteredLightBars[i], filteredLightBars[j]);

                        if(fabs(armor.angle) > ::armorPara.maxArmorErrorAngle && fabs(armor.angle) < 180.0f - ::armorPara.maxArmorErrorAngle)
                            continue;



                        armorStruct.lightAngle = lightBarsAngle;
                        armorStruct.partLightBars[0] = (filteredLightBars[i].center.x < filteredLightBars[j].center.x ? filteredLightBars[i] : filteredLightBars[j]);
                        armorStruct.partLightBars[1] = (filteredLightBars[i].center.x > filteredLightBars[j].center.x ? filteredLightBars[i] : filteredLightBars[j]);
                        armorStruct.hitPoint = ArmorTool::getCrossPoint(shortCenter0[0],shortCenter1[1],shortCenter0[1], shortCenter1[0]);
                        armorStruct.armorRect = armor;

                        //ArmorTool::drawRotatedRect(src, armor, cv::Scalar(0, 165, 255), 2, 16);
                        //cv::circle(src, armorStruct.hitPoint, 1, cv::Scalar(0, 165, 255), 4);  // 画半径为1的圆(画点）
                        IdentifyArmor::ClassificationArmor(armorStruct);
                        armorStructs.push_back(armorStruct);
                        /*
                        cv::line(src, shortCenter0[0],shortCenter1[1], cv::Scalar(219,112,147),1);
                        cv::line(src, shortCenter0[1], shortCenter1[0], cv::Scalar(219,112,147),1);
                        cv::circle(src, armorStruct.hitPoint, 1, cv::Scalar(255, 255, 255), 4);
                         */

                    }
                }
            }
        }
    }
}

void IdentifyArmor::FilterErrorArmor() {
    float centreDistance[2];
    for(int i = 0; i < armorStructs.size(); i++){
        for(int j = 0; j < filteredLightBars.size(); j++){
            centreDistance[0] = ArmorTool::getTwoPointDistance(armorStructs[i].partLightBars[1].center, filteredLightBars[j].center);
            centreDistance[1] = ArmorTool::getTwoPointDistance(armorStructs[i].partLightBars[0].center, filteredLightBars[j].center);
            if (centreDistance[0] && centreDistance[1]) {
                if (ArmorTool::embeddedRectJudge(armorStructs[i].armorRect, filteredLightBars[j])) {
                    armorStructs.erase(std::begin(armorStructs) + i);
                    break;
                }
            }
        }
    }

    if (armorStructs.size() <= 1) {
        return;
    }

    for (int i = 0; i < armorStructs.size() - 1; ++i) {
        for (int j = i + 1; j < armorStructs.size(); ++j) {
            centreDistance[0] = ArmorTool::getTwoPointDistance(armorStructs[i].partLightBars[1].center, armorStructs[j].partLightBars[0].center);
            centreDistance[1] = ArmorTool::getTwoPointDistance(armorStructs[i].partLightBars[0].center, armorStructs[j].partLightBars[1].center);
            if (!centreDistance[0]) {

                if(armorStructs[i].armorType == true && armorStructs[j].armorType == true) {
                    if (armorStructs[i].lightAngle > armorStructs[j].lightAngle) {
                        armorStructs.erase(std::begin(armorStructs) + i);
                    }
                    else if (armorStructs[i].lightAngle < armorStructs[j].lightAngle) {
                        armorStructs.erase(std::begin(armorStructs) + j);
                    } else {
                        if (armorStructs[i].armorRect.size.width/armorStructs[i].armorRect.size.height > armorStructs[j].armorRect.size.width/armorStructs[j].armorRect.size.height) {
                            armorStructs.erase(std::begin(armorStructs) + i);
                        } else {
                            armorStructs.erase(std::begin(armorStructs) + j);
                        }
                    }
                } else {
                    if (armorStructs[i].armorRect.size.width/armorStructs[i].armorRect.size.height > armorStructs[j].armorRect.size.width/armorStructs[j].armorRect.size.height) {
                        armorStructs.erase(std::begin(armorStructs) + i);
                    } else {
                        armorStructs.erase(std::begin(armorStructs) + j);
                    }
                }
            }
            else if (!centreDistance[1]) {


                if(armorStructs[i].armorType == true && armorStructs[j].armorType == true){
                    if (armorStructs[i].lightAngle > armorStructs[j].lightAngle) {
                        armorStructs.erase(std::begin(armorStructs) + i);
                    }
                    else if (armorStructs[i].lightAngle < armorStructs[j].lightAngle) {
                        armorStructs.erase(std::begin(armorStructs) + j);
                    } else {
                        if (armorStructs[i].armorRect.size.width/armorStructs[i].armorRect.size.height > armorStructs[j].armorRect.size.width/armorStructs[j].armorRect.size.height) {
                            armorStructs.erase(std::begin(armorStructs) + i);
                        } else {
                            armorStructs.erase(std::begin(armorStructs) + j);
                        }
                    }
                } else {
                    if (armorStructs[i].armorRect.size.width/armorStructs[i].armorRect.size.height > armorStructs[j].armorRect.size.width/armorStructs[j].armorRect.size.height) {
                        armorStructs.erase(std::begin(armorStructs) + i);
                    } else {
                        armorStructs.erase(std::begin(armorStructs) + j);
                    }
                }
            }
        }
    }

    if (armorStructs.size() <= 1) {
        return;
    }

    for (int i = 0; i < armorStructs.size() - 1; ++i) {
        for (int j = i + 1; j < armorStructs.size(); ++j) {
            if((armorStructs[i].armorRect.size.width / armorStructs[j].armorRect.size.width <= armorPara.reflectionError) && (armorStructs[i].armorRect.center.x / armorStructs[j].armorRect.center.x) <= armorPara.reflectionError){
                if (armorStructs[i].armorRect.center.y < armorStructs[j].armorRect.center.y){
                    armorStructs.erase(std::begin(armorStructs) + j);
                }
                else{
                    armorStructs.erase(std::begin(armorStructs) + i);
                }

                //std::cout << abs(armorStructs[i].armorRect.center.x - armorStructs[j].armorRect.center.x) << std::endl;
            }

        }
    }

}

void IdentifyArmor::ClassificationArmor(ArmorStruct& armorStructs) {
    float longSide_1 = ArmorTool::findExtremumOfSide(armorStructs.partLightBars[0], LONG_SIDE);
    float longSide_2 = ArmorTool::findExtremumOfSide(armorStructs.partLightBars[1], LONG_SIDE);
    float heightScale = longSide_1 > longSide_2 ? (longSide_1 / longSide_2) : (longSide_2 / longSide_1);

    if (ArmorTool::getRectLengthWidthRatio(armorStructs.armorRect) > 3.3f) {
        //_bigArmorFlag = true;
        armorStructs.armorType = 1;
    }
    else if (ArmorTool::getRectLengthWidthRatio(armorStructs.armorRect) > 2.6f) {
        if (heightScale > 1.3f) {
            //_bigArmorFlag = true;
            armorStructs.armorType = 1;
        }
        else {
            armorStructs.armorType = 0;
        }
    }
    else armorStructs.armorType = 0;
}

void IdentifyArmor::TargetSelection() {
    if (armorStructs.empty()) {
        lastArmorTarget = cv::Rect(0, 0, 0, 0);
        return;
    }
    else{
        float maxArmor = 0;
        for (int i = 0; i < armorStructs.size(); ++i) {
            if (armorStructs[i].armorRect.size.width * armorStructs[i].armorRect.size.height > maxArmor){
                maxArmor = armorStructs[i].armorRect.size.width * armorStructs[i].armorRect.size.height;
                targetArmorIdex = i;
            }
        }

        if(_cropRoi){
            armorStructs[targetArmorIdex].hitPoint.x = armorStructs[targetArmorIdex].hitPoint.x + cropOriginPoint.x;
            armorStructs[targetArmorIdex].hitPoint.y = armorStructs[targetArmorIdex].hitPoint.y + cropOriginPoint.y;
        }

        lastArmorTarget = armorStructs[targetArmorIdex].armorRect.boundingRect();;
        ArmorKCF::_targetArmorFind= true;
    }
}

/*
void IdentifyArmor::CropRoi(const cv::Mat &src) {

    const cv::Point& lastArmorTargetCenter = cv::Point (lastArmorTarget.x + 1/2*lastArmorTarget.width, lastArmorTarget.y + 1/2*lastArmorTarget.height);

    if (lastArmorTarget.width * lastArmorTarget.height){
        //返回包含旋转矩形的最小右上整数矩形。
        static float ratioToWidth = 2.0f;
        static float ratioToHeight = 3.0f;

        int x1 = MAX(int(lastArmorTargetCenter.x - (lastArmorTarget.width * ratioToWidth)), 0);
        int y1 = MAX(int(lastArmorTargetCenter.y - (lastArmorTarget.height * ratioToHeight)), 0);
        cv::Point lu = cv::Point(x1, y1);                                                           //得到点lu，ROI左上角的起点
        cropOriginPoint = lu;
        int x2 = MIN(int(lastArmorTargetCenter.x + (lastArmorTarget.width * ratioToWidth)), src.cols);                //计算结果不大于图片长宽
        int y2 = MIN(int(lastArmorTargetCenter.y + (lastArmorTarget.height * ratioToHeight)), src.rows);
        cv::Point rd = cv::Point(x2, y2);                                                           //得到点rd，ROI右下角的终点
        restoreRect = cv::Rect(lu, rd);

        rectangle(src,restoreRect, cv::Scalar(0, 255, 255));

        src(restoreRect).copyTo(searchSrc);

        cv::imshow("12", searchSrc);
        cv::waitKey(100);
    }
    else{
        searchSrc = src;                                                        //继承原图片地址
        //restoreRect = cv::Rect(0, 0, src.cols, src.rows);
    }
    //cv::waitKey(10);
}*/




