//
// Created by root on 2022/3/10.
//

#include "armor-KCF.hpp"
/*
using namespace std;
using namespace Eigen;
using namespace cv;

bool ArmorKCF::start = false;

Matrix4f A;
Matrix4f state;
Matrix4f H;
Matrix4f P;
Matrix4f Q;
Matrix4f R;
Matrix4f y;
Matrix4f K, S;
Matrix4f Si;
Matrix4f I;
Matrix2f S1, S2;

ArmorKCF::ArmorKCF() {}

void ArmorKCF::kalmanUpd(bool start, float measX, float measY) {

    A <<    1, 0, 1, 0,
            0, 1, 0, 1,
            0, 0, 1, 0,
            0, 0, 0, 1;

    H <<    1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;

    Q <<    0.1, 0, 0, 0,
            0, 0.1, 0, 0,
            0, 0, 0.1, 0,
            0, 0, 0, 0.1;

    I <<    1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    R <<    1, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;



    y <<    measX, 0, 0, 0,
            measY, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;

    if (!start){
        state << 0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0;

        P <<    1000, 0, 0, 0,
                0, 1000, 0, 0,
                0, 0, 1000, 0,
                0, 0, 0, 1000;

        //   start = true;
    }

    S = H * P * H.transpose() + R;
    S1(0,0) = S(0,0);
    S1(1,0) = S(1,0);
    S1(0,1) = S(0,1);
    S1(1,1) = S(1,1);

    S2 = S1.inverse();
    Si(0,0) = S2(0,0);
    Si(0,1) = S2(0,1);
    Si(1,0) = S2(1,0);
    Si(1,1) = S2(1,1);
    K = P * H.transpose() * Si;
    state = state + K * (y - H * state);
    P = (I - K * H) * P;
    //cout << state << endl << endl;

    // cout << measX << endl;
}

void ArmorKCF::kalmanPred(bool start) {
    A <<    1, 0, 1, 0,
            0, 1, 0, 1,
            0, 0, 1, 0,
            0, 0, 0, 1;

    Q <<    100, 0, 0, 0,
            0, 100, 0, 0,
            0, 0, 100, 0,
            0, 0, 0, 100;

    state = A * state;
    P = A * P * A.transpose() + Q;
}

static ArmorPara armorPara = ArmorParaFactory::getArmorPara();*/
/*
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
        trackerInit = true;
}
*/