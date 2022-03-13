//
// Created by root on 2022/3/10.
//

#include "armor-KCF.hpp"

static ArmorPara armorPara = ArmorParaFactory::getArmorPara();

ArmorKCF::ArmorKCF() {}

cv::Ptr<cv::TrackerKCF> ArmorKCF::trackerKCF = cv::TrackerKCF::create();

int ArmorKCF::srcWidth = 1280;
int ArmorKCF::srcHeight = 640;

cv::Mat ArmorKCF::searchingSrc( 640, 480, CV_8UC3, cv::Scalar(0,255,0) );

cv::Rect ArmorKCF::trackingRect = cv::Rect(0, 0, 0, 0);
cv::Rect ArmorKCF::searchingRect = cv::Rect(0, 0, 0, 0);

bool ArmorKCF::trackerIsReady = false;
bool ArmorKCF::trackerSuccess = false;
bool ArmorKCF::trackerInit = false;

void ArmorKCF::trackingStart(cv::RotatedRect targetArmor, cv::RotatedRect targetArmorLightBar_L, cv::RotatedRect targetArmorLightBar_R) {

    float lightBarWidth_L  = targetArmorLightBar_L.size.width < targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
    float lightBarHeight_L = targetArmorLightBar_L.size.width > targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
    float lightBarWidth_R  = targetArmorLightBar_R.size.width < targetArmorLightBar_R.size.height ? targetArmorLightBar_R.size.width : targetArmorLightBar_R.size.height;
    float lightBarHeight_R = targetArmorLightBar_R.size.width > targetArmorLightBar_R.size.height ? targetArmorLightBar_R.size.width : targetArmorLightBar_R.size.height;

    cv::Point2d trackingRect_tl = cv::Point2d((double)(targetArmorLightBar_L.center.x - 1.1 * lightBarWidth_L), (double)(targetArmorLightBar_L.center.y - 1.2 * lightBarHeight_L));
    cv::Point2d trackingRect_br = cv::Point2d((double)(targetArmorLightBar_R.center.x + 1.1 * lightBarWidth_R), (double)(targetArmorLightBar_R.center.y + 1.2 * lightBarHeight_R));

    //recttl += cv::Point2d(searchRect.x, searchRect.y);
    //rectbr += cv::Point2d(searchRect.x, searchRect.y);
    trackingRect = cv::Rect2d(trackingRect_tl, trackingRect_br);
    trackingRect &= cv::Rect(0, 0, srcWidth, srcHeight);

    rectangle(IdentifyArmor::src, trackingRect, cv::Scalar(0, 255, 255));
    //std::cout << 1111 << std::endl;
    //std::cout << trackingRect.width << " " << trackingRect.height << std::endl;
    if(!(trackingRect & cv::Rect(0, 0, searchingSrc.cols, searchingSrc.rows)).empty()){
        trackerKCF = cv::TrackerKCF::create();
        trackerKCF->init(searchingSrc, trackingRect);
        trackerInit = true;
    }
}

void ArmorKCF::trackerUpdate(const cv::Mat &src) {
    armorPara.detect_thresh = 0.03f;
    if (trackerIsReady && trackerInit) {
        src.copyTo(searchingSrc);

        if (!trackerKCF->update(searchingSrc, trackingRect)) {
            trackerSuccess = false;
            searchingRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
        }
        else if ((trackingRect & cv::Rect(0, 0, srcWidth, srcHeight)) != trackingRect) {
            trackerSuccess = false;
            searchingRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
        }
        else {
            trackerSuccess = true;
            searchingRect.x = trackingRect.x - trackingRect.width / 4;
            searchingRect.y = trackingRect.y - trackingRect.height / 4;
            searchingRect.height = trackingRect.height * 1.5;
            searchingRect.width = trackingRect.width * 1.5;
            searchingRect &= cv::Rect(0, 0, srcWidth, srcHeight);
        }
        //src(searchingRect).copyTo(src);
        src(searchingRect).copyTo(searchingSrc);
        cv::imshow("", searchingSrc);
        cv::waitKey(1);
    }
}
    //armorPara.enemyColor = enemyColor;
/*
    if (trackingInProgress) {
        //追踪失败
        src(trackerRect).copyTo(img);
        if (!trackerKCF->update(trackingSrc, trackerRect)) {
            trackerSuccess = false;
            searchRect.x = trackerRect.x - trackerRect.width;
            searchRect.y = trackerRect.y - trackerRect.height;
            searchRect.height = trackerRect.height * 3;
            searchRect.width = trackerRect.width * 3;
            searchRect & cv::Rect(0, 0, srcWidth, srcHeight);
        }
        else {
            //越界则需要从全图搜索
            if ((trackerRect & cv::Rect(0, 0, srcWidth, srcHeight)) != trackerRect) {
                searchRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
            }
                //搜索区域需要扩大两倍
            else {
                trackerSuccess = true;
                //searchRect.x = trackerRect.x - trackerRect.width / 2;
                //searchRect.y = trackerRect.y - trackerRect.height / 2;
                //searchRect.height = trackerRect.height * 2;
                //searchRect.width = trackerRect.width * 2;
                searchRect &= cv::Rect(0, 0, srcWidth, srcHeight);
            }
        }
        src(searchRect).copyTo(trackingSrc);
        cv::imshow("img", img);
    }
    else {
        trackerSuccess = false;
        searchRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
        trackingSrc = src;
    }

    imshow("Tacking Src", trackingSrc);
    cv::waitKey(1);

}*/
/*
void ArmorKCF::trackerCallBack(cv::Mat src) {
    const cv::Point& lastResult = resLast.center;                         //上一个运行结果取上一次方框的中心
    if (lastResult.x == 0 || lastResult.y == 0) {                          //如果上一次结果的x或y为0，就以整个图片的大小作方框
        trackingSrc = src;                                                        //继承原图片地址
        restoreRect = cv::Rect(0, 0, src.cols, src.rows);
        firstLoad = true;
    }
    else {                                                                //否则继承上一次的图片大小
        firstLoad = false;
        cv::Rect rect = resLast.boundingRect();                            //返回包含旋转矩形的最小右上整数矩形。
        static float ratioToWidth = 4.8f;
        static float ratioToHeight = 3.0f;
        int x1 = MAX(int(lastResult.x - (rect.width * ratioToWidth)), 0);
        int y1 = MAX(int(lastResult.y - (rect.height * ratioToHeight)), 0);
        cv::Point lu = cv::Point(x1, y1);                                                           //得到点lu，ROI左上角的起点
        int x2 = MIN(int(lastResult.x + (rect.width * ratioToWidth)), src.cols);                //计算结果不大于图片长宽
        int y2 = MIN(int(lastResult.y + (rect.height * ratioToHeight)), src.rows);
        cv::Point rd = cv::Point(x2, y2);                                                           //得到点rd，ROI右下角的终点
        restoreRect = cv::Rect(lu, rd);
        src(restoreRect).copyTo(src);
    }

}

/*
bool ArmorKCF::trackingInProgress = false;
bool ArmorKCF::trackerFindTarget = false;
bool ArmorKCF::trackerSuccess = false;
bool ArmorKCF::findReulst = false;
bool ArmorKCF::firstLoad = false;

cv::Rect ArmorKCF::trackerRect = cv::Rect(0, 0, 0, 0);
cv::Rect ArmorKCF::searchRect = cv::Rect(0, 0, 0, 0);

int ArmorKCF::srcWidth = 1280;
int ArmorKCF::srcHeight = 640;

cv::Size ArmorKCF::_size = cv::Size_(1280, 640);
cv::Mat ArmorKCF::trackingSrc;

cv::RotatedRect ArmorKCF::resultRect;
cv::RotatedRect ArmorKCF::resLast;
cv::Rect ArmorKCF::restoreRect;

cv::Point2f ArmorKCF::vertices[4];

cv::Ptr<cv::TrackerKCF> ArmorKCF::trackerKCF = cv::TrackerKCF::create();

void ArmorKCF::trackerInit(const cv::Mat& src, EnemyColor enemyColor) {
    cv::Mat img;
    _size = src.size();
    armorPara.enemyColor = enemyColor;
    armorPara.detect_thresh = 0.03f;
    if (trackingInProgress) {
        //追踪失败
        src(trackerRect).copyTo(img);
        if (!trackerKCF->update(trackingSrc, trackerRect)) {
            trackerSuccess = false;
            searchRect.x = trackerRect.x - trackerRect.width;
            searchRect.y = trackerRect.y - trackerRect.height;
            searchRect.height = trackerRect.height * 3;
            searchRect.width = trackerRect.width * 3;
            searchRect & cv::Rect(0, 0, srcWidth, srcHeight);
        }
        else {
            //越界则需要从全图搜索
            if ((trackerRect & cv::Rect(0, 0, srcWidth, srcHeight)) != trackerRect) {
                searchRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
            }
                //搜索区域需要扩大两倍
            else {
                trackerSuccess = true;
                //searchRect.x = trackerRect.x - trackerRect.width / 2;
                //searchRect.y = trackerRect.y - trackerRect.height / 2;
                //searchRect.height = trackerRect.height * 2;
                //searchRect.width = trackerRect.width * 2;
                searchRect &= cv::Rect(0, 0, srcWidth, srcHeight);
            }
        }
        src(searchRect).copyTo(trackingSrc);
        cv::imshow("img", img);
    }
    else {
        trackerSuccess = false;
        searchRect = cv::Rect2d(0, 0, srcWidth, srcHeight);
        trackingSrc = src;
    }

    imshow("Tacking Src", trackingSrc);
    cv::waitKey(1);
}

void ArmorKCF::trackerStart(cv::RotatedRect resultRect, cv::RotatedRect targetArmorLightBar_L, cv::RotatedRect rightLightBar) {
    //if (findReulst) {
        float lightBarWidthL = targetArmorLightBar_L.size.width < targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
        float lightBarHeightL = targetArmorLightBar_L.size.width > targetArmorLightBar_L.size.height ? targetArmorLightBar_L.size.width : targetArmorLightBar_L.size.height;
        float lightBarWidthR = rightLightBar.size.width < rightLightBar.size.height ? rightLightBar.size.width : rightLightBar.size.height;
        float lightBarHeightR = rightLightBar.size.width > rightLightBar.size.height ? rightLightBar.size.width : rightLightBar.size.height;

        cv::Point2d recttl = cv::Point2d((double)(targetArmorLightBar_L.center.x - 2.0 * lightBarWidthL), (double)(targetArmorLightBar_L.center.y - 1.5 * lightBarHeightL));
        cv::Point2d rectbr = cv::Point2d((double)(rightLightBar.center.x + 2.0 * lightBarWidthR), (double)(rightLightBar.center.y + 1.5 * lightBarHeightR));

        recttl += cv::Point2d(searchRect.x, searchRect.y);
        rectbr += cv::Point2d(searchRect.x, searchRect.y);
        trackerRect = cv::Rect2d(recttl, rectbr);
        trackerRect &= cv::Rect(0, 0, srcWidth, srcHeight);
        trackerKCF = cv::TrackerKCF::create();

        //trackerRect =  cv::Rect(0, 0, 100, 100);

        trackerKCF->init(trackingSrc, trackerRect);

    //}
    resultRect.center += cv::Point2f((float)searchRect.x, (float)searchRect.y);

    resultRect.points(vertices);
    //记录上一刻的检测区域
    resLast = resultRect;
    //_lost_cnt = 0;
    //记录上一刻的时间
    //_lastTime = (double)(cv::getTickCount());
}

void ArmorKCF::trackerCallBack(cv::Mat src) {
    const cv::Point& lastResult = resLast.center;                         //上一个运行结果取上一次方框的中心
    if (lastResult.x == 0 || lastResult.y == 0) {                          //如果上一次结果的x或y为0，就以整个图片的大小作方框
        trackingSrc = src;                                                        //继承原图片地址
        restoreRect = cv::Rect(0, 0, src.cols, src.rows);
        firstLoad = true;
    }
    else {                                                                //否则继承上一次的图片大小
        firstLoad = false;
        cv::Rect rect = resLast.boundingRect();                            //返回包含旋转矩形的最小右上整数矩形。
        static float ratioToWidth = 4.8f;
        static float ratioToHeight = 3.0f;
        int x1 = MAX(int(lastResult.x - (rect.width * ratioToWidth)), 0);
        int y1 = MAX(int(lastResult.y - (rect.height * ratioToHeight)), 0);
        cv::Point lu = cv::Point(x1, y1);                                                           //得到点lu，ROI左上角的起点
        int x2 = MIN(int(lastResult.x + (rect.width * ratioToWidth)), src.cols);                //计算结果不大于图片长宽
        int y2 = MIN(int(lastResult.y + (rect.height * ratioToHeight)), src.rows);
        cv::Point rd = cv::Point(x2, y2);                                                           //得到点rd，ROI右下角的终点
        restoreRect = cv::Rect(lu, rd);
        src(restoreRect).copyTo(src);
    }

}
*/


