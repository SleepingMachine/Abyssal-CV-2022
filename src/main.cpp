#include "camera/camera-stream.hpp"
#include "armor/armor-identify.hpp"
#include "video/video-save.hpp"
#include "control/control-switch.hpp"
#include "serial/serial-TUP/serial-port-TUP.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <opencv2/core/core.hpp>

extern std::mutex mutex1;
extern std::mutex mutex2;

extern std::atomic_bool CameraisOpen;
extern std::atomic_bool SerialPortStart;

static int sentPortData;

int main(int argc, char* argv[]) {
    CameraisOpen = true;
    SerialPortStart = true;
    cv::Mat frame(1280, 720, CV_8UC3), gray;

    //if (!ControlSwitch::functionConfig._enableLocalVideoStreaming){
        //CameraStream::InitCamera();
    //}
    //std::thread serial_thread(SerialPort::SendData, &sentPortData);
    std::thread serial_thread(SerialPortTUP::SerialSynchronize);
    //std::thread Synchronize_thread();
    std::thread camera_thread(CameraStream::StreamRetrieve, &frame);
    //std::thread armor_thread(IdentifyArmor::ArmorIdentifyStream, &frame, &sendData);
    std::thread control_thread(ControlSwitch::SwitchMode, &frame, &sentPortData);
    std::thread video_thread(VideoSave::SaveRunningVideo, &frame);
    //TODO：监控线程、通信线程/
    /*
    while(CameraisOpen) {
        mutex1.lock();
        frame.copyTo(gray);
        mutex1.unlock();
        if (gray.empty()) {
            std::cout << "Get Frame Fail" << std::endl;
            break;
        }
        cv::imshow("video", gray);
        cv::waitKey(5);
    }
    */
    serial_thread.join();
    camera_thread.join();
    //armor_thread.join();
    control_thread.join();
    video_thread.join();
    CameraStream::UnInitCamera();

    return 0;
}