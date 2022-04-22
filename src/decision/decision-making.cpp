//
// Created by sleepingmachine on 22-4-21.
//

#include "decision-making.hpp"

extern std::mutex mutex2;
extern std::atomic_bool IdentifyStart;

using namespace cv;

int DecisionMaking::tempPointData = 0;
int DecisionMaking::lastPointData = 0;

DecisionMaking::DecisionMaking() {}
void DecisionMaking::DecisionStream(int *rawData) {
    KalmanDemo2(rawData);
}

int DecisionMaking::KalmanDemo(int *rawData) {
    {
        Mat img;
        if (ControlSwitch::functionConfig._enableEnergyBuffMode) {
            img = Mat(640, 960, CV_8UC3);
        } else {
            img = Mat(480, 960, CV_8UC3);
        }

        KalmanFilter KF(2, 1, 0);
        Mat state(2, 1, CV_32F); /* (phi, delta_phi) */
        Mat processNoise(2, 1, CV_32F);
        Mat measurement = Mat::zeros(1, 1, CV_32F);
        char code = (char) -1;

        for (;;) {
            img = Scalar::all(0);
            state.at<float>(0) = 0.0f;
            state.at<float>(1) = 2.f * (float) CV_PI / 6;
            KF.transitionMatrix = (Mat_<float>(2, 2) << 1, 1, 0, 1);

            setIdentity(KF.measurementMatrix);
            setIdentity(KF.processNoiseCov, Scalar::all(1e-5));
            setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
            setIdentity(KF.errorCovPost, Scalar::all(1));

            randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));

            for (;;) {
                if (mutex2.try_lock()) {
                    tempPointData = *rawData;
                    mutex2.unlock();
                }
                int tempPointData_y = tempPointData % 1000;
                int tempPointData_x = (tempPointData - tempPointData_y)/1000;

                Point2f center(img.cols * 0.5f, img.rows * 0.5f);
                float R = img.cols / 3.f;
                double stateAngle = state.at<float>(0);
                Point statePt = calcPoint(center, R, stateAngle);

                Mat prediction = KF.predict();
                double predictAngle = prediction.at<float>(0);
                Point predictPt = calcPoint(center, R, predictAngle);

                // generate measurement
                randn(measurement, Scalar::all(0), Scalar::all(KF.measurementNoiseCov.at<float>(0)));
                measurement += KF.measurementMatrix * state;

                double measAngle = measurement.at<float>(0);
                Point measPt = calcPoint(center, R, measAngle);

                // correct the state estimates based on measurements
                // updates statePost & errorCovPost
                KF.correct(measurement);
                double improvedAngle = KF.statePost.at<float>(0);
                Point improvedPt = calcPoint(center, R, improvedAngle);

                // plot points
                img = img * 0.2;
                drawMarker(img, measPt, Scalar(0, 0, 255), cv::MARKER_SQUARE, 5, 2);
                drawMarker(img, predictPt, Scalar(0, 255, 255), cv::MARKER_SQUARE, 5, 2);
                drawMarker(img, improvedPt, Scalar(0, 255, 0), cv::MARKER_SQUARE, 5, 2);
                drawMarker(img, statePt, Scalar(255, 255, 255), cv::MARKER_STAR, 10, 1);
                // forecast one step
                Mat test = Mat(KF.transitionMatrix * KF.statePost);
                drawMarker(img, calcPoint(center, R, Mat(KF.transitionMatrix * KF.statePost).at<float>(0)),
                           Scalar(255, 255, 0), cv::MARKER_SQUARE, 12, 1);

                line(img, statePt, measPt, Scalar(0, 0, 255), 1, LINE_AA, 0);
                line(img, statePt, predictPt, Scalar(0, 255, 255), 1, LINE_AA, 0);
                line(img, statePt, improvedPt, Scalar(0, 255, 0), 1, LINE_AA, 0);


                randn(processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));
                state = KF.transitionMatrix * state + processNoise;

                imshow("Kalman", img);
                code = (char) waitKey(500);

                if (code > 0)
                    break;
            }
            if (code == 27 || code == 'q' || code == 'Q')
                break;
        }

        return 0;
    }
}


void DecisionMaking::KalmanDemo2(int *rawData) {
    const int winHeight=640;
    const int winWidth=960;
    RNG rng;
    //1.kalman filter setup
    const int stateNum=4;                                      //状态值4×1向量(x,y,△x,△y)
    const int measureNum=2;                                    //测量值2×1向量(x,y)
    KalmanFilter KF(stateNum, measureNum, 0);

    KF.transitionMatrix = (Mat_<float>(4, 4) <<    //转移矩阵A
            1,0,1,0,
            0,1,0,1,
            0,0,1,0,
            0,0,0,1);
    setIdentity(KF.measurementMatrix);                                                    //测量矩阵H
    setIdentity(KF.processNoiseCov, Scalar::all(1e-5));                            //系统噪声方差矩阵Q
    setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));                        //测量噪声方差矩阵R
    setIdentity(KF.errorCovPost, Scalar::all(1));                                  //后验错误估计协方差矩阵P
    rng.fill(KF.statePost,RNG::UNIFORM,0,winHeight>winWidth?winWidth:winHeight);   //初始状态值x(0)
    Mat measurement = Mat::zeros(measureNum, 1, CV_32F);                           //初始测量值x'(0)，因为后面要更新这个值，所以必须先定义

    namedWindow("kalman");
    //setMouseCallback("kalman",mouseEvent);

    Mat image(winHeight,winWidth,CV_8UC3,Scalar(0));

    while (1)
    {
        if (mutex2.try_lock()) {
            tempPointData = *rawData;
            mutex2.unlock();
        }
        int tempPointData_y = tempPointData % 1000;
        int tempPointData_x = (tempPointData - tempPointData_y)/1000;
        if (tempPointData_x  && tempPointData_y){
            //2.kalman prediction
            Mat prediction = KF.predict();
            Point predict_pt = Point(prediction.at<float>(0),prediction.at<float>(1) );   //预测值(x',y')

            //3.update measurement
            measurement.at<float>(0) = tempPointData_x;
            measurement.at<float>(1) = tempPointData_y;

            //4.update
            KF.correct(measurement);

            //draw
            image.setTo(Scalar(255,255,255,0));
            circle(image,predict_pt,5,Scalar(0,255,0),3);    //predicted point with green
            circle(image,cv::Point(tempPointData_x,tempPointData_y),5,Scalar(255,0,0),3); //current position with red

            imshow("kalman", image);
        }

    }
}


