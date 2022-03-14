//
// Created by root on 2022/3/10.
//

#include "armor-KCF.hpp"

ArmorKCF::ArmorKCF() {}
static ArmorPara armorPara = ArmorParaFactory::getArmorPara();

cv::Rect ArmorKCF::trackingRect = cv::Rect(0, 0, 0, 0);
cv::Rect ArmorKCF::searchingRect = cv::Rect(0, 0, 0, 0);

void ArmorKCF::trackerInit(cv::RotatedRect targetArmor, cv::RotatedRect targetArmorLightBar_L, cv::RotatedRect targetArmorLightBar_R) {
    float lightBarWidth_L  = targetArmorLightBar_L.size.width < targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
    float lightBarHeight_L = targetArmorLightBar_L.size.width > targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
    float lightBarWidth_R  = targetArmorLightBar_R.size.width < targetArmorLightBar_R.size.height ? targetArmorLightBar_R.size.width : targetArmorLightBar_R.size.height;
    float lightBarHeight_R = targetArmorLightBar_R.size.width > targetArmorLightBar_R.size.height ? targetArmorLightBar_R.size.width : targetArmorLightBar_R.size.height;

    cv::Point2d trackingRect_tl = cv::Point2d((double)(targetArmorLightBar_L.center.x - 1.1 * lightBarWidth_L), (double)(targetArmorLightBar_L.center.y - 1.2 * lightBarHeight_L));
    cv::Point2d trackingRect_br = cv::Point2d((double)(targetArmorLightBar_R.center.x + 1.1 * lightBarWidth_R), (double)(targetArmorLightBar_R.center.y + 1.2 * lightBarHeight_R));
/*
    //recttl += cv::Point2d(searchRect.x, searchRect.y);
    //rectbr += cv::Point2d(searchRect.x, searchRect.y);
    trackingRect = cv::Rect2d(trackingRect_tl, trackingRect_br);
    trackingRect &= cv::Rect(0, 0, srcWidth, srcHeight);
    rectangle(IdentifyArmor::src, trackingRect, cv::Scalar(0, 255, 255), 3);
    if(!(trackingRect & cv::Rect(0, 0, searchingSrc.cols, searchingSrc.rows)).empty()){
        trackerKCF = cv::TrackerKCF::create();
        trackerKCF->init(searchingSrc, trackingRect);
        //previousResultRect = targetArmor;
        trackerInit = true;*/
}
