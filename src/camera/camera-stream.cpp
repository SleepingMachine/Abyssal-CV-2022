//
// Created by sleepingmachine on 2021/11/30.
//
#include "camera-stream.hpp"

using namespace cv;

unsigned char           * g_pRgbBuffer;     //处理后数据缓存区
int                     iCameraCounts = 1;
int                     iStatus=-1;
tSdkCameraDevInfo       tCameraEnumList;
int                     hCamera;
tSdkCameraCapbility     tCapability;      //设备描述信息
tSdkFrameHead           sFrameInfo;
BYTE*			        pbyBuffer;
int                     iDisplayFrames = 10000;
IplImage *iplImage =    NULL;
int                     channel=3;

std::mutex mutex1;
std::atomic_bool CameraisOpen;

int CameraStream::InitCamera() {


    CameraSdkInit(1);

    //枚举设备，并建立设备列表
    iStatus = CameraEnumerateDevice(&tCameraEnumList,&iCameraCounts);
    printf("state = %d\n", iStatus);

    printf("count = %d\n", iCameraCounts);
    //没有连接设备
    if(iCameraCounts==0){
        printf("no camera find");
        exit(0);
        return -1;
    }

    //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    iStatus = CameraInit(&tCameraEnumList,-1,-1,&hCamera);

    //初始化失败
    printf("state = %d\n", iStatus);
    if(iStatus!=CAMERA_STATUS_SUCCESS){
        exit(0);
        return -1;
    }

    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    CameraGetCapability(hCamera,&tCapability);

    //
    g_pRgbBuffer = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);
    //g_readBuf = (unsigned char*)malloc(tCapability.sResolutionRange.iHeightMax*tCapability.sResolutionRange.iWidthMax*3);

    /*让SDK进入工作模式，开始接收来自相机发送的图像
    数据。如果当前相机是触发模式，则需要接收到
    触发帧以后才会更新图像。    */
    CameraPlay(hCamera);

    CameraSetTriggerMode(hCamera, 0);
    CameraSetAeState(hCamera, false);
    CameraSetExposureTime(hCamera, 10 * 1000);
    SetCameraResolution(hCamera, 0, 0, 960, 640);

    /*其他的相机参数设置
    例如 CameraSetExposureTime   CameraGetExposureTime  设置/读取曝光时间
         CameraSetImageResolution  CameraGetImageResolution 设置/读取分辨率
         CameraSetGamma、CameraSetConrast、CameraSetGain等设置图像伽马、对比度、RGB数字增益等等。
         更多的参数的设置方法，，清参考MindVision_Demo。本例程只是为了演示如何将SDK中获取的图像，转成OpenCV的图像格式,以便调用OpenCV的图像处理函数进行后续开发
    */

    if(tCapability.sIspCapacity.bMonoSensor){
        channel=1;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_MONO8);
    }else{
        channel=3;
        CameraSetIspOutFormat(hCamera,CAMERA_MEDIA_TYPE_BGR8);
    }
    return 0;
}

void CameraStream::UnInitCamera() {
    CameraUnInit(hCamera);
    //注意，现反初始化后再free
    free(g_pRgbBuffer);
}


void CameraStream::StreamRetrieve(cv::Mat* pFrame) {
    //显示图像
    while (CameraisOpen) {
        if (CameraGetImageBuffer(hCamera, &sFrameInfo, &pbyBuffer, 1000) == CAMERA_STATUS_SUCCESS) {
            CameraImageProcess(hCamera, pbyBuffer, g_pRgbBuffer, &sFrameInfo);

            cv::Mat matImage(
                    cvSize(sFrameInfo.iWidth, sFrameInfo.iHeight),
                    sFrameInfo.uiMediaType == CAMERA_MEDIA_TYPE_MONO8 ? CV_8UC1 : CV_8UC3,
                    g_pRgbBuffer
            );
            //imshow("Opencv Demo", matImage);

            if (mutex1.try_lock()) {
                matImage.copyTo(*pFrame);
                mutex1.unlock();
            }
            waitKey(5);

            //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
            //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
            CameraReleaseImageBuffer(hCamera, pbyBuffer);

        }
    }
}


int CameraStream::SetCameraResolution(int hCamera, int offsetx, int offsety, int width, int height)
{
    tSdkImageResolution sRoiResolution = { 0 };

    // 设置成0xff表示自定义分辨率，设置成0到N表示选择预设分辨率
    // Set to 0xff for custom resolution, set to 0 to N for select preset resolution
    sRoiResolution.iIndex = 0xff;

    // iWidthFOV表示相机的视场宽度，iWidth表示相机实际输出宽度
    // 大部分情况下iWidthFOV=iWidth。有些特殊的分辨率模式如BIN2X2：iWidthFOV=2*iWidth，表示视场是实际输出宽度的2倍
    // iWidthFOV represents the camera's field of view width, iWidth represents the camera's actual output width
    // In most cases iWidthFOV=iWidth. Some special resolution modes such as BIN2X2:iWidthFOV=2*iWidth indicate that the field of view is twice the actual output width
    sRoiResolution.iWidth = width;
    sRoiResolution.iWidthFOV = width;

    // 高度，参考上面宽度的说明
    // height, refer to the description of the width above
    sRoiResolution.iHeight = height;
    sRoiResolution.iHeightFOV = height;

    // 视场偏移
    // Field of view offset
    sRoiResolution.iHOffsetFOV = offsetx;
    sRoiResolution.iVOffsetFOV = offsety;

    // ISP软件缩放宽高，都为0则表示不缩放
    // ISP software zoom width and height, all 0 means not zoom
    sRoiResolution.iWidthZoomSw = 0;
    sRoiResolution.iHeightZoomSw = 0;

    // BIN SKIP 模式设置（需要相机硬件支持）
    // BIN SKIP mode setting (requires camera hardware support)
    sRoiResolution.uBinAverageMode = 0;
    sRoiResolution.uBinSumMode = 0;
    sRoiResolution.uResampleMask = 0;
    sRoiResolution.uSkipMode = 0;

    return CameraSetImageResolution(hCamera, &sRoiResolution);
}
