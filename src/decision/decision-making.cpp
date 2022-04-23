//
// Created by sleepingmachine on 22-4-21.
//

#include "decision-making.hpp"

extern std::mutex mutex2;
extern std::atomic_bool IdentifyStart;

using namespace std;
using namespace Eigen;
using namespace cv;

bool start = false;

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

int DecisionMaking::tempPointData = 0;
int DecisionMaking::lastPointData = 0;

DecisionMaking::DecisionMaking() {}
void DecisionMaking::DecisionStream(int *rawData) {
    KalmanTracking(rawData);
}

int DecisionMaking::KalmanDemo1(int *rawData) {
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

                //Point2f center(img.cols * 0.5f, img.rows * 0.5f);
                //float R = img.cols / 3.f;
                //double stateAngle = state.at<float>(0);
                //Point statePt = calcPoint(center, R, stateAngle);
                Point statePt = cv::Point(tempPointData_x, tempPointData_y);

                Mat prediction = KF.predict();
                //double predictAngle = prediction.at<float>(0);
                //Point predictPt = calcPoint(center, R, predictAngle);
                Point predictPt = Point(prediction.at<float>(0),prediction.at<float>(1) );   //预测值(x',y')

                // generate measurement
                //randn(measurement, Scalar::all(0), Scalar::all(KF.measurementNoiseCov.at<float>(0)));
                //measurement += KF.measurementMatrix * state;
                measurement.at<float>(0) = tempPointData_x;
                measurement.at<float>(1) = tempPointData_y;

                //double measAngle = measurement.at<float>(0);
                //Point measPt = calcPoint(center, R, measAngle);

                // correct the state estimates based on measurements
                // updates statePost & errorCovPost
                KF.correct(measurement);
                //double improvedAngle = KF.statePost.at<float>(0);
                //Point improvedPt = calcPoint(center, R, improvedAngle);

                // plot points
                img = img * 0.2;
                //drawMarker(img, measPt, Scalar(0, 0, 255), cv::MARKER_SQUARE, 5, 2);
                drawMarker(img, predictPt, Scalar(0, 255, 255), cv::MARKER_SQUARE, 5, 2);
                //drawMarker(img, improvedPt, Scalar(0, 255, 0), cv::MARKER_SQUARE, 5, 2);
                drawMarker(img, statePt, Scalar(255, 255, 255), cv::MARKER_STAR, 10, 1);
                // forecast one step
                Mat test = Mat(KF.transitionMatrix * KF.statePost);
               // drawMarker(img, calcPoint(center, R, Mat(KF.transitionMatrix * KF.statePost).at<float>(0)),
               //            Scalar(255, 255, 0), cv::MARKER_SQUARE, 12, 1);

                //line(img, statePt, measPt, Scalar(0, 0, 255), 1, LINE_AA, 0);
                line(img, statePt, predictPt, Scalar(0, 255, 255), 1, LINE_AA, 0);
                //line(img, statePt, improvedPt, Scalar(0, 255, 0), 1, LINE_AA, 0);

                randn(processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));
                state = KF.transitionMatrix * state + processNoise;

                imshow("Kalman", img);
                code = (char) waitKey(10);

            }
        }

        return 0;
    }
}

void DecisionMaking::KalmanDemo2(int *rawData) {

    //int _test_falg = 0;
    const int winHeight=640;
    const int winWidth=960;
    RNG rng;
    //1.kalman filter setup
    const int stateNum=4;                                      //状态值4×1向量(x,y,△x,△y)
    const int measureNum=4;                                    //测量值4×1向量(x,y,△x,△y)
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

        int lastPointData_y = lastPointData % 1000;
        int lastPointData_x = (lastPointData - lastPointData_y)/1000;
        if (tempPointData_x  && tempPointData_y){
            //2.kalman prediction
            Mat prediction = KF.predict();
            Point predict_pt = Point(prediction.at<float>(0),prediction.at<float>(1) );   //预测值(x',y')

            //3.update measurement
            measurement.at<float>(0) = tempPointData_x;
            measurement.at<float>(1) = tempPointData_y;
            measurement.at<float>(3) = (tempPointData_x - lastPointData_x);
            measurement.at<float>(4) = (tempPointData_y - lastPointData_y);

            //4.update
            /*
            if (_test_falg % 5 == 0){
                KF.correct(measurement);
            }
            _test_falg++;
            */
            KF.correct(measurement);

            //draw
            image.setTo(Scalar(255,255,255,0));
            circle(image,predict_pt,5,Scalar(0,255,0),3);    //predicted point with green
            circle(image,cv::Point(tempPointData_x,tempPointData_y),5,Scalar(255,0,0),3); //current position with red
            lastPointData = tempPointData;
            imshow("kalman", image);
        }

    }
}

void DecisionMaking::kalmanUpd(bool start, float measX, float measY) {

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

void DecisionMaking::kalmanPred(bool start) {
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

int DecisionMaking::KalmanTracking(int *rawData) {
    int winHeight = 640;
    int winWidth  = 960;
    Mat res(winHeight,winWidth,CV_8UC3,Scalar(0));
    while(IdentifyStart){
        if (mutex2.try_lock()) {
            tempPointData = *rawData;
            mutex2.unlock();
        }
        int tempPointData_y = tempPointData % 1000;
        int tempPointData_x = (tempPointData - tempPointData_y)/1000;
        if (tempPointData_x && tempPointData_y){
            cv::Point center;
            center.x = tempPointData_x;
            center.y = tempPointData_y;
            kalmanUpd(start, center.x, center.y);
            start = true;
        }
        kalmanPred(start);
        res.setTo(Scalar(255,255,255,0));
        cv::circle(res, cv::Point(tempPointData_x, tempPointData_y), 10, CV_RGB(0,255,255), 2.5);
        cv::circle(res, cv::Point(state(0,0), state(1,0)), 20, CV_RGB(0,0,255), 2.5);
        imshow("efghoepb", res);
    }
    return 0;
}



