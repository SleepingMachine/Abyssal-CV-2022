//
// Created by root on 2022/3/10.
//

#include "armor-KCF.hpp"

static ArmorPara armorPara = ArmorParaFactory::getArmorPara();


ArmorKCF::ArmorKCF() {}

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
                searchRect.x = trackerRect.x - trackerRect.width / 2;
                searchRect.y = trackerRect.y - trackerRect.height / 2;
                searchRect.height = trackerRect.height * 2;
                searchRect.width = trackerRect.width * 2;
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

void ArmorKCF::trackerStart(cv::RotatedRect resultRect, cv::RotatedRect leftLightBar, cv::RotatedRect rightLightBar) {
    std::cout << findReulst << std::endl;
    if (findReulst) {
        std::cout << 1111 << std::endl;
        float lightBarWidthL = leftLightBar.size.width < leftLightBar.size.height ? leftLightBar.size.width : leftLightBar.size.height;
        float lightBarHeightL = leftLightBar.size.width > leftLightBar.size.height ? leftLightBar.size.width : leftLightBar.size.height;
        float lightBarWidthR = rightLightBar.size.width < rightLightBar.size.height ? rightLightBar.size.width : rightLightBar.size.height;
        float lightBarHeightR = rightLightBar.size.width > rightLightBar.size.height ? rightLightBar.size.width : rightLightBar.size.height;

        cv::Point2d recttl = cv::Point2d((double)(leftLightBar.center.x - 2.0 * lightBarWidthL), (double)(leftLightBar.center.y - 1.5 * lightBarHeightL));
        cv::Point2d rectbr = cv::Point2d((double)(rightLightBar.center.x + 2.0 * lightBarWidthR), (double)(rightLightBar.center.y + 1.5 * lightBarHeightR));

        recttl += cv::Point2d(searchRect.x, searchRect.y);
        rectbr += cv::Point2d(searchRect.x, searchRect.y);
        trackerRect = cv::Rect2d(recttl, rectbr);
        trackerRect &= cv::Rect(0, 0, srcWidth, srcHeight);
        trackerKCF = cv::TrackerKCF::create();
        trackerKCF->init(trackingSrc, trackerRect);

    }
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

