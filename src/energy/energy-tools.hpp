//
// Created by sleepingmachine on 2022/3/29.
//

#ifndef ABYSSAL_CV_2022_ENERGY_TOOLS_HPP
#define ABYSSAL_CV_2022_ENERGY_TOOLS_HPP

#include <opencv2/imgproc/imgproc.hpp>

class EnergyBuffTool{
public:
    static inline float findExtremumOfSide(cv::RotatedRect &rect, bool flag) {
        if (flag)
            return rect.size.height > rect.size.width ? rect.size.height : rect.size.width;
        else
            return rect.size.height < rect.size.width ? rect.size.height : rect.size.width;
    }

    static inline float getRectLengthWidthRatio(cv::RotatedRect &rect) {
        float longSide = rect.size.height > rect.size.width ? rect.size.height : rect.size.width;   //获取识别出矩形长
        float shortSide = rect.size.height < rect.size.width ? rect.size.height : rect.size.width;  //获取识别出矩形宽
        return longSide / shortSide;
    }

    static inline float lineToLineAngle(cv::Point2f &p1, cv::Point2f &p2, cv::Point2f &p3, cv::Point2f &p4) {
        if (p2.x == p1.x) {
            p2.x += 1e-10f;
        }
        if (p3.x == p4.x) {
            p3.x += 1e-10f;
        }
        float tan1 = (p2.y - p1.y) / (p2.x - p1.x);
        float tan2 = (p4.y - p3.y) / (p4.x - p3.x);
        float angle1 = radianToAngle(atanf(tan1));
        float angle2 = radianToAngle(atanf(tan2));
        float skew = fabs(fabs(angle1 - angle2) - 90);
        return 90.0f - skew;
    }


    static inline float radianToAngle(float p) {
        return p * 180.0f / PI_F();
    }

    static inline float PI_F() {
        return float(CV_PI);
    }

    static inline float getTwoPointDistance(cv::Point2f point_1, cv::Point2f point_2) {
        return sqrtf(pow((point_1.x - point_2.x), 2) + pow((point_1.y - point_2.y), 2));
    }

    static void getShortCenter(cv::RotatedRect rect, cv::Point2f* shortCenter) {
        if (rect.size.width <= 0) {
            return;
        }
        cv::Point2f verts[4];
        rect.points(verts);
        if (getTwoPointDistance(verts[0], verts[1]) < getTwoPointDistance(verts[1], verts[2])) {
            shortCenter[0] = (verts[0] + verts[1]) / 2;
            shortCenter[1] = (verts[2] + verts[3]) / 2;
        }
        else {
            shortCenter[0] = (verts[1] + verts[2]) / 2;
            shortCenter[1] = (verts[3] + verts[0]) / 2;
        }
    }

    static inline float getLightBarTan(cv::RotatedRect filteredLightBars){
        float tan = 0.0f;
        cv::Point2f vertices[4];
        filteredLightBars.points(vertices);

        if (fabs(vertices[0].x - vertices[2].x) > fabs(vertices[1].x - vertices[3].x)) {
            if (vertices[0].y > vertices[2].y) {
                tan = (vertices[0].y - vertices[2].y) / vertices[0].x - vertices[2].x;
            }
            else {
                tan = (vertices[2].y - vertices[0].y) / vertices[2].x - vertices[0].x;
            }
        }
        else {
            if (vertices[1].y > vertices[3].y) {
                tan = (vertices[1].y - vertices[3].y) / vertices[1].x - vertices[3].x;
            }
            else {
                tan = (vertices[3].y - vertices[1].y) / vertices[3].x - vertices[1].x;
            }
        }

        return tan;
    }

    static float calSkewingAngle(cv::RotatedRect rect1, cv::RotatedRect rect2, cv::Point2f* shortCenter) {
        if (rect1.size.width <= 0 || rect1.size.height <= 0) {
            return float();
        }
        return lineToLineAngle(rect1.center, rect2.center, shortCenter[0], shortCenter[1]);
    }

    static cv::RotatedRect assembleArmor(cv::RotatedRect rect0, cv::RotatedRect rect1){
        const cv::Point2f &pl = rect0.center, pr = rect1.center;
        cv::Point2f center = (pl + pr) / 2.0;
        float long_1 = findExtremumOfSide(rect0, LONG_SIDE);
        float long_2 = findExtremumOfSide(rect1, LONG_SIDE);
        float width = getTwoPointDistance(pl, pr);
        float height = (long_2 + long_1) / (float) 2.0;
        float angle = std::atan2(rect1.center.y - rect0.center.y, rect1.center.x - rect0.center.x);
        return cv::RotatedRect(center, cv::Size2f(width, height), angle * 180 / PI_F());
    }

    static inline void drawRotatedRect(cv::Mat mask,const cv::RotatedRect &rotatedrect,const cv::Scalar &color,int thickness, int lineType)
    {
        // 提取旋转矩形的四个角点
        cv::Point2f ps[4];
        rotatedrect.points(ps);

        // 构建轮廓线
        std::vector<std::vector<cv::Point>> tmpContours;    // 创建一个InputArrayOfArrays 类型的点集
        std::vector<cv::Point> contours;
        for (int i = 0; i != 4; ++i) {
            contours.emplace_back(cv::Point2i(ps[i]));
        }
        tmpContours.insert(tmpContours.end(), contours);

        // 绘制轮廓，即旋转矩形
        drawContours(mask, tmpContours, 0, color,thickness, lineType);  // 填充mask
    }

    static inline cv::Point2f getCrossPoint(cv::Point2f line1, cv::Point2f line2, cv::Point2f line3, cv::Point2f line4) //交点
    {
        double x_member, x_denominator, y_member, y_denominator;
        cv::Point2f cross_point;
        x_denominator = line4.x*line2.y - line4.x*line1.y - line3.x*line2.y + line3.x*line1.y
                        - line2.x*line4.y + line2.x*line3.y + line1.x*line4.y - line1.x*line3.y;

        x_member = line3.y*line4.x*line2.x - line4.y*line3.x*line2.x - line3.y*line4.x*line1.x + line4.y*line3.x*line1.x
                   - line1.y*line2.x*line4.x + line2.y*line1.x*line4.x + line1.y*line2.x*line3.x - line2.y*line1.x*line3.x;

        if (x_denominator == 0)
            cross_point.x = 0;
        else
            cross_point.x = x_member / x_denominator;

        y_denominator = line4.y*line2.x - line4.y*line1.x - line3.y*line2.x + line1.x*line3.y
                        - line2.y*line4.x + line2.y*line3.x + line1.y*line4.x - line1.y*line3.x;

        y_member = -line3.y*line4.x*line2.y + line4.y*line3.x*line2.y + line3.y*line4.x*line1.y - line4.y*line3.x*line1.y
                   + line1.y*line2.x*line4.y - line1.y*line2.x*line3.y - line2.y*line1.x*line4.y + line2.y*line1.x*line3.y;

        if (y_denominator == 0)
            cross_point.y = 0;
        else
            cross_point.y = y_member / y_denominator;

        return cross_point;  //平行返回(0,0)
    }

    static bool embeddedRectJudge(cv::RotatedRect r1, cv::RotatedRect r2) {
        double distance = r1.size.width > r1.size.height ? r1.size.width / 2 : r1.size.height / 2;

        return (getTwoPointDistance(r1.center, r2.center) < distance);
    }

    static inline bool makeRectSafe(cv::Rect &rect, const cv::Size &size) {
        if (rect.x < 0)
            rect.x = 0;
        if (rect.x + rect.width > size.width)
            rect.width = size.width - rect.x;
        if (rect.y < 0)
            rect.y = 0;
        if (rect.y + rect.height > size.height)
            rect.height = size.height - rect.y;
        return !(rect.width <= 0 || rect.height <= 0);
    }

};
#endif //ABYSSAL_CV_2022_ENERGY_TOOLS_HPP
