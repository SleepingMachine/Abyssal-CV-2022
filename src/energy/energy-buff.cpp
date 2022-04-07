//
// Created by sleepingmachine on 2022/3/25.
//

#include "energy-buff.hpp"

//默认hsv颜色阈值

IdentifyEnergyBuff::IdentifyEnergyBuff() {
    rLogoCenterSVM = cv::Algorithm::load<cv::ml::SVM>("../asset/TrainData/CIRCLE_SVM_DATA.xml");
}

int IdentifyEnergyBuff::hmin_0 = 0;
int IdentifyEnergyBuff::hmax_0 = 0;
int IdentifyEnergyBuff::smin_0 = 0;
int IdentifyEnergyBuff::smax_0 = 0;
int IdentifyEnergyBuff::vmin_0 = 0;
int IdentifyEnergyBuff::vmax_0 = 0;

int IdentifyEnergyBuff::hmin_1 = 0;
int IdentifyEnergyBuff::hmax_1 = 0;
int IdentifyEnergyBuff::smin_1 = 0;
int IdentifyEnergyBuff::smax_1 = 0;
int IdentifyEnergyBuff::vmin_1 = 0;
int IdentifyEnergyBuff::vmax_1 = 0;

//默认二值化操作阈值
int IdentifyEnergyBuff::open   = 1;
int IdentifyEnergyBuff::close  = 6;
int IdentifyEnergyBuff::erode  = 2;
int IdentifyEnergyBuff::dilate = 4;

float IdentifyEnergyBuff::rLogoRectLongSide    = 0;
float IdentifyEnergyBuff::rLogoRectArea        = 0;

cv::Point_<float> IdentifyEnergyBuff::rLogoRectCenterPoint = cv::Point_<float>(0,0);

bool IdentifyEnergyBuff::_findEnergyBuffTarget = false;
bool IdentifyEnergyBuff::_cropRoi = false;

cv::Point IdentifyEnergyBuff::cropOriginPoint;

cv::RotatedRect IdentifyEnergyBuff::rLogoRect;

std::vector<std::vector<cv::Point2i> > IdentifyEnergyBuff::allContours;
std::vector<cv::Vec4i> IdentifyEnergyBuff::hierarchy;

std::vector<cv::RotatedRect> IdentifyEnergyBuff::possibleBladeRects;
std::vector<cv::RotatedRect> IdentifyEnergyBuff::possibleRLogoRects;

std::vector<int> IdentifyEnergyBuff::possibleBladeRectParentProfiles;
std::vector<int> IdentifyEnergyBuff::possibleBladeRectChildProfiles;

std::vector<float> IdentifyEnergyBuff::possibleBladeRectsArea;

static EnergyBuffPara energyBuffPara = EnergyBuffParaFactory::getEnergyBuffPara();

cv::Mat IdentifyEnergyBuff::src(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::srcHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::searchSrc(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::testSearch(640, 960, CV_8UC3);;
cv::Mat IdentifyEnergyBuff::maskHSV(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_0(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::maskHSV_1(640, 960, CV_8UC3);
cv::Mat IdentifyEnergyBuff::dstHSV(640, 960, CV_8UC3);

cv::Ptr<cv::ml::SVM> IdentifyEnergyBuff::rLogoCenterSVM;

void IdentifyEnergyBuff::EnergyBuffIdentifyStream(cv::Mat importSrc, int *sendData) {
    src = importSrc;
    IdentifyEnergyBuff();

    //DynamicResolutionResize();
    //ImagePreprocess(searchSrc);
    ImagePreprocess(src);

    searchContours_PossibleRect();
    searchContours_BuffCenter(possibleRLogoRects);
    searchContours_Cantilever(possibleBladeRects);

    DrawReferenceGraphics();
    resourceRelease();
}

void IdentifyEnergyBuff::ImagePreprocess(const cv::Mat &src) {
    cv::cvtColor(src, srcHSV, CV_BGR2HSV, 0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_0, IdentifyEnergyBuff::smin_0, IdentifyEnergyBuff::vmin_0), cv::Scalar(IdentifyEnergyBuff::hmax_0, IdentifyEnergyBuff::smax_0, IdentifyEnergyBuff::vmax_0), maskHSV_0);
    cv::inRange(srcHSV, cv::Scalar(IdentifyEnergyBuff::hmin_1, IdentifyEnergyBuff::smin_1, IdentifyEnergyBuff::vmin_1), cv::Scalar(IdentifyEnergyBuff::hmax_1, IdentifyEnergyBuff::smax_1, IdentifyEnergyBuff::vmax_1), maskHSV_1);
    //cv::imshow("0", maskHSV_0);
    //cv::imshow("1", maskHSV_1);
    maskHSV = maskHSV_0 | maskHSV_1;
    //maskHSV = maskHSV_1;
    cv::GaussianBlur(dstHSV, dstHSV, cv::Size(5, 5), 3, 3);
    morphologyEx(maskHSV, dstHSV, 2, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::open,IdentifyEnergyBuff::open)));
    morphologyEx(dstHSV, dstHSV, 3, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::close,IdentifyEnergyBuff::close)));
    morphologyEx(dstHSV, dstHSV, 0, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::erode,IdentifyEnergyBuff::erode)));
    morphologyEx(dstHSV, dstHSV, 1, getStructuringElement(cv::MORPH_RECT,cv::Size(IdentifyEnergyBuff::dilate,IdentifyEnergyBuff::dilate)));
}

void IdentifyEnergyBuff::CreatTrackbars() {
    cv::namedWindow("能量机关识别中的阈值调整",cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("hmin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmin_0, 255,NULL);
    cv::createTrackbar("hmax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmax_0, 255,NULL);
    cv::createTrackbar("smin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smin_0, 255,NULL);
    cv::createTrackbar("smax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smax_0, 255,NULL);
    cv::createTrackbar("vmin0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmin_0, 255,NULL);
    cv::createTrackbar("vmax0", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmax_0, 255,NULL);

    cv::createTrackbar("hmin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmin_1, 255,NULL);
    cv::createTrackbar("hmax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::hmax_1, 255,NULL);
    cv::createTrackbar("smin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smin_1, 255,NULL);
    cv::createTrackbar("smax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::smax_1, 255,NULL);
    cv::createTrackbar("vmin1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmin_1, 255,NULL);
    cv::createTrackbar("vmax1", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::vmax_1, 255,NULL);

    cv::createTrackbar("open", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::open, 10,NULL);
    cv::createTrackbar("close", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::close, 30,NULL);
    cv::createTrackbar("erode", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::erode, 10,NULL);
    cv::createTrackbar("dilate", "能量机关识别中的阈值调整",&IdentifyEnergyBuff::dilate, 20,NULL);
}

void IdentifyEnergyBuff::searchContours_PossibleRect() {
    cv::findContours(dstHSV, allContours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    std::vector<std::vector<cv::Point2i> >::iterator it_allContours = allContours.begin();

    for (int i = 0; i < allContours.size(); ++i) {
        cv::RotatedRect scanRect = minAreaRect(allContours[i]);
        float area = float(cv::contourArea(allContours[i]));
        float longSide = EnergyBuffTool::findExtremumOfSide(scanRect, LONG_SIDE);
        float shortSide = EnergyBuffTool::findExtremumOfSide(scanRect, SHORT_SIDE);
        if (scanRect.size.area() < energyBuffPara.minBuffCenterRectArea){
            continue;
        }
        if (longSide / shortSide <= 1.5) {
            possibleRLogoRects.push_back(scanRect);
            continue;
        }
        else if(scanRect.size.area() <= 2 * rLogoRect.size.area())
        {
            continue;
        }
        /*
        for (int j = 0; j < 4; ++j) {
            std::cout << hierarchy[i][j] << " ";
        }
        std::cout << std::endl;
        */
        //std::cout << hierarchy.size() << " " << allContours.size() << std::endl;
        possibleBladeRectParentProfiles.push_back(hierarchy[i][3]);
        possibleBladeRectChildProfiles.push_back(hierarchy[i][2]);
        possibleBladeRects.push_back(scanRect);
        possibleBladeRectsArea.push_back(area);
    }

    /*
    int i = 0;
    while (it_allContours != allContours.end()) {
        cv::RotatedRect scanRect = minAreaRect(*it_allContours);   //检测最小面积的矩形
        float area = float(cv::contourArea(allContours[i]));
        ++it_allContours;
        float longSide = EnergyBuffTool::findExtremumOfSide(scanRect, LONG_SIDE);
        float shortSide = EnergyBuffTool::findExtremumOfSide(scanRect, SHORT_SIDE);

        if (longSide / shortSide <= 1.2) {
            possibleRLogoRects.push_back(scanRect);
            continue;
        }
        else if(_findEnergyBuffTarget && scanRect.size.area() <= 2 * rLogoRect.size.area())
        {
            continue;
        }

        std::cout << hierarchy.size() << " " << allContours.size() << std::endl;
        possibleBladeRectParentProfiles.push_back(hierarchy[i][2]);
        possibleBladeRectChildProfiles.push_back(hierarchy[i][3]);
        possibleBladeRects.push_back(scanRect);
        possibleBladeRectsArea.push_back(area);
        i++;
    }*/
}

void IdentifyEnergyBuff::resourceRelease() {
    allContours.clear();
    hierarchy.clear();
    possibleBladeRects.clear();
    //possibleRLogoRects.clear();
    possibleBladeRectChildProfiles.clear();
    possibleBladeRectParentProfiles.clear();
    //rLogoRectCenterPoint = cv::Point(0,0);
    //_findEnergyBuffTarget = false;
    //_cropRoi = false;
}

void IdentifyEnergyBuff::searchContours_BuffCenter(std::vector<cv::RotatedRect> possibleRLogoRects) {
    //如果轮廓容量为零则返回
    //_findRectFlag = false;
    if (IdentifyEnergyBuff::possibleRLogoRects.empty()) {
        _findEnergyBuffTarget = false;
        return;
    }
    //bool findFlag = false;

    //筛选圆心矩形
    for (int i = 0; i < possibleRLogoRects.size(); i++) {
        if (possibleRLogoRects[i].size.area() < energyBuffPara.minBuffCenterRectArea) {
            _findEnergyBuffTarget = false;
            continue;
        }
        //如果轮廓不是类正方形，则跳过
        if ((possibleRLogoRects[i].size.width / possibleRLogoRects[i].size.height) > 1.2 ||
            (possibleRLogoRects[i].size.width / possibleRLogoRects[i].size.height) < 0.8) {
            _findEnergyBuffTarget = false;
            continue;
        }

        if (!circleCenterSVM(possibleRLogoRects[i])) {
            _findEnergyBuffTarget = false;
            continue;
        }

        rLogoRect = possibleRLogoRects[i];
        _findEnergyBuffTarget = true;
    }

    if (_findEnergyBuffTarget){
        rLogoRectLongSide = rLogoRect.size.width > rLogoRect.size.height? rLogoRect.size.width : rLogoRect.size.height;
        rLogoRectArea = rLogoRect.size.area();
        if (_cropRoi){
            rLogoRectCenterPoint.x = rLogoRect.center.x + cropOriginPoint.x;
            rLogoRectCenterPoint.y = rLogoRect.center.y + cropOriginPoint.y;
            //_cropRoi = false;
        }
        else{
            rLogoRectCenterPoint = rLogoRect.center;
        }
    }
}

bool IdentifyEnergyBuff::circleCenterSVM(cv::RotatedRect &inputRect){
    std::vector<cv::RotatedRect> outputRects;
    cv::Point2f v[4];
    inputRect.points(v);
    float longSide  = EnergyBuffTool::getTwoPointDistance(v[0], v[1]) < EnergyBuffTool::getTwoPointDistance(v[2], v[1])? EnergyBuffTool::getTwoPointDistance(v[2], v[1]) : EnergyBuffTool::getTwoPointDistance(v[0], v[1]);
    float shortSide = EnergyBuffTool::getTwoPointDistance(v[0], v[1]) < EnergyBuffTool::getTwoPointDistance(v[2], v[1])? EnergyBuffTool::getTwoPointDistance(v[0], v[1]) : EnergyBuffTool::getTwoPointDistance(v[2], v[1]);

    cv::Rect _bounding_roi = inputRect.boundingRect();
    cv::Mat roi_circleCenter;
    if (_bounding_roi.width < _bounding_roi.height) {
        cv::Point center((_bounding_roi.tl().x + _bounding_roi.br().x) / 2,
                         (_bounding_roi.tl().y + _bounding_roi.br().y) / 2);
        cv::Point half(_bounding_roi.height / 2, _bounding_roi.width / 2);
        _bounding_roi = cv::Rect(center - half, center + half);                                    //重新定位tl和br
    }
    //都加上长的一边是为了保证仿射变换后有完整的图进行检测
    _bounding_roi.x -= (int) (shortSide / 2);
    _bounding_roi.width += (int) shortSide;
    _bounding_roi.y -= (int) (shortSide / 2);
    _bounding_roi.height += (int) shortSide;
    if (!EnergyBuffTool::makeRectSafe(_bounding_roi, srcHSV.size())) {
        return bool();
    }
    srcHSV(_bounding_roi).copyTo(roi_circleCenter);
    cv::Mat rectify_target = roi_circleCenter.clone();
    transpose(rectify_target, rectify_target);
    cv::Point half((int) (1.0f * longSide) / 2, (int) (1.0f * shortSide / 2));
    cv::Point roiCenter(rectify_target.cols / 2, rectify_target.rows / 2);
    cv::Point addOther(10, 10);
    cv::Rect sampleRoiRect = cv::Rect(roiCenter - half - addOther, roiCenter + half + addOther);
    sampleRoiRect.x = MAX(sampleRoiRect.x, 0);                        //确保矩形不越界
    sampleRoiRect.y = MAX(sampleRoiRect.y, 0);
    if (!EnergyBuffTool::makeRectSafe(sampleRoiRect, rectify_target.size())) {
        return bool();
    }
    cv::Mat sample = rectify_target(sampleRoiRect);//重新定位tl和br
    cv::resize(sample, sample, cv::Size(30, 30), 0, 0);
    //_circleSampleData.image = sample;
    cv::cvtColor(sample, sample, cv::COLOR_HSV2BGR);
    cv::cvtColor(sample, sample, cv::COLOR_BGR2GRAY);
    cv::imshow("1",sample);
    cv::Mat p = sample.reshape(1, 1);
    p.convertTo(p, CV_32FC1);
    normalize(p, p);
    int response = 0;
    response = (int) rLogoCenterSVM->predict(p);
    //setSampleCaptureState(true);
    _findEnergyBuffTarget = true;
    if (!response) {
        //_circleSampleData.classifyState = false;
        return false;
    }
    //_circleSampleData.classifyState = true;
    return true;

}

void IdentifyEnergyBuff::DrawReferenceGraphics() {
    if (_findEnergyBuffTarget){
        EnergyBuffTool::drawRotatedRect(src,rLogoRect,cv::Scalar(25,255,25),2, 16);
        cv::circle(src, rLogoRectCenterPoint, 1, cv::Scalar(51,48,245), 2);  // 画半径为1的圆(画点）
        cv::circle(src, cropOriginPoint, 1, cv::Scalar(51,48,245), 2);  // 画半径为1的圆(画点）
    }

    for (int i = 0; i < possibleBladeRects.size(); ++i) {
        if(possibleBladeRectParentProfiles[i] == -1){
            EnergyBuffTool::drawRotatedRect(src,possibleBladeRects[i],cv::Scalar(204,209,72),2, 16);
        }
        else{
            EnergyBuffTool::drawRotatedRect(src,possibleBladeRects[i],cv::Scalar(4,159,72),2, 16);
        }
    }

    cv::imshow("Seach", searchSrc);
    cv::imshow("Dst", dstHSV);
    cv::imshow("Energy", src);
}

void IdentifyEnergyBuff::searchContours_Cantilever(std::vector<cv::RotatedRect> possibleBladeRects) {
    if (possibleBladeRects.empty() || !_findEnergyBuffTarget) {
        return;
    }
/*
    for (int i = 0; i < possibleBladeRectParentProfiles.size(); ++i) {
        std::cout << possibleBladeRectParentProfiles[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < possibleBladeRectChildProfiles.size(); ++i) {
        std::cout << possibleBladeRectChildProfiles[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;*/

    for (int i = 0; i < possibleBladeRects.size(); ++i) {
        int childRectsCounter = 0;
        if (EnergyBuffTool::getTwoPointDistance(possibleBladeRects[i].center, rLogoRectCenterPoint) > 12 * rLogoRectLongSide) {
            possibleBladeRects.erase(possibleBladeRects.begin()+i);
            possibleBladeRectParentProfiles.erase(possibleBladeRectParentProfiles.begin()+i);
            possibleBladeRectChildProfiles.erase(possibleBladeRectChildProfiles.begin()+i);
            continue;
        }
        if (possibleBladeRectParentProfiles[i] == -1){
            for (int j = i+1; j < possibleBladeRectParentProfiles.size() ; ++j) {
                if(possibleBladeRectParentProfiles[j] == possibleBladeRectParentProfiles[i+1])
                    ++childRectsCounter;
            }
            /*
            //EnergyBuffTool::drawRotatedRect(src, possibleBladeRects[i], cv::Scalar(0,0,255),5, 16);
            for (int j = 0; j < possibleBladeRectParentProfiles.size(); ++j) {

                if (possibleBladeRectParentProfiles[j] == i+1 || (i == 0 && possibleBladeRectParentProfiles[j] == 0)){
                    ++childRectsCounter;
                }


            }*/
        }
        if (childRectsCounter == 1){
            EnergyBuffTool::drawRotatedRect(src, possibleBladeRects[i], cv::Scalar(0,0,255),2, 16);
            if (possibleBladeRectChildProfiles[i] != -1){
                cv::circle(src, possibleBladeRects[i+1].center, 20, cv::Scalar(0, 127, 255), 2);  // 画半径为1的圆(画点）
            }
        }
        if (childRectsCounter == 2){
            EnergyBuffTool::drawRotatedRect(src, possibleBladeRects[i], cv::Scalar(0,255,0),2, 16);
        }
        if (childRectsCounter == 3){
            EnergyBuffTool::drawRotatedRect(src, possibleBladeRects[i], cv::Scalar(255,0,0),2, 16);
        }
    }
}

void IdentifyEnergyBuff::DynamicResolutionResize() {
    cv::Point roi_UL = cv::Point(0,0);
    cv::Point roi_LR = cv::Point(960,640);
    std::cout << _findEnergyBuffTarget << " " << _cropRoi << std::endl;
    if (_findEnergyBuffTarget && !_cropRoi){
        roi_UL.x = rLogoRectCenterPoint.x - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.x - 12 * rLogoRectLongSide;
        roi_UL.y = rLogoRectCenterPoint.y - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.y - 12 * rLogoRectLongSide;

        roi_LR.x = rLogoRectCenterPoint.x + 10 * rLogoRectLongSide > 960? 960 : rLogoRectCenterPoint.x + 12 * rLogoRectLongSide;
        roi_LR.y = rLogoRectCenterPoint.y + 10 * rLogoRectLongSide > 640? 640 : rLogoRectCenterPoint.y + 12 * rLogoRectLongSide;
        cropOriginPoint = roi_UL;
        _cropRoi = true;
    }
    else if (_findEnergyBuffTarget && _cropRoi){
        /*
        roi_UL.x = rLogoRectCenterPoint.x - 10 * rLogoRectLongSide + rLogoRectCenterPoint.x < 0? 0 : rLogoRectCenterPoint.x - 12 * rLogoRectLongSide + rLogoRectCenterPoint.x;
        roi_UL.y = rLogoRectCenterPoint.y - 10 * rLogoRectLongSide + rLogoRectCenterPoint.y < 0? 0 : rLogoRectCenterPoint.y - 12 * rLogoRectLongSide + rLogoRectCenterPoint.y;

        roi_LR.x = rLogoRectCenterPoint.x + 10 * rLogoRectLongSide + rLogoRectCenterPoint.x > 960? 960 : rLogoRectCenterPoint.x + 12 * rLogoRectLongSide + rLogoRectCenterPoint.x;
        roi_LR.y = rLogoRectCenterPoint.y + 10 * rLogoRectLongSide + rLogoRectCenterPoint.y > 640? 640 : rLogoRectCenterPoint.y + 12 * rLogoRectLongSide + rLogoRectCenterPoint.y;
        */
        roi_UL.x = rLogoRectCenterPoint.x - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.x - 12 * rLogoRectLongSide;
        roi_UL.y = rLogoRectCenterPoint.y - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.y - 12 * rLogoRectLongSide;

        roi_LR.x = rLogoRectCenterPoint.x + 10 * rLogoRectLongSide > 960? 960 : rLogoRectCenterPoint.x + 12 * rLogoRectLongSide;
        roi_LR.y = rLogoRectCenterPoint.y + 10 * rLogoRectLongSide > 640? 640 : rLogoRectCenterPoint.y + 12 * rLogoRectLongSide;
         cropOriginPoint = roi_UL;
        _cropRoi = true;
        std::cout << 2 << std::endl;
    }
    else{
        roi_UL = cv::Point(0,0);
        roi_LR = cv::Point(960,640);
        cropOriginPoint = roi_UL;
        _cropRoi = false;
    }
    /*
    testSearch = src(cv::Rect(roi_UL,roi_LR));

    cv::imshow("121", testSearch);
    */
    searchSrc = src(cv::Rect(roi_UL,roi_LR));
    //cv::rectangle(src, roi_LR, roi_UL, cv::Scalar(255, 255, 255), 2);
    //cv::waitKey(1500);
    /*
    if (!_findEnergyBuffTarget && !_cropRoi){
        searchSrc = src(cv::Rect(roi_UL,roi_LR));
        cropOriginPoint = roi_LR;
        _cropRoi = false;
    }

    if (_findEnergyBuffTarget && !_cropRoi){
    //if (_findEnergyBuffTarget && !_cropRoi){
        roi_UL.x = rLogoRectCenterPoint.x - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.x - 10 * rLogoRectLongSide;
        roi_UL.y = rLogoRectCenterPoint.y - 10 * rLogoRectLongSide < 0? 0 : rLogoRectCenterPoint.y - 10 * rLogoRectLongSide;

        roi_LR.x = rLogoRectCenterPoint.x + 10 * rLogoRectLongSide > 960? 960 : rLogoRectCenterPoint.x + 10 * rLogoRectLongSide;
        roi_LR.y = rLogoRectCenterPoint.y + 10 * rLogoRectLongSide > 640? 640 : rLogoRectCenterPoint.y + 10 * rLogoRectLongSide;
        std::cout << roi_UL.x << " " << roi_UL.y << " " << roi_LR.x << " " << roi_LR.y << std::endl;
        searchSrc = src(cv::Rect(roi_UL,roi_LR));
        cropOriginPoint = roi_LR;
        _cropRoi = true;
        //= rLogoRect.center;
    }
     */

}
