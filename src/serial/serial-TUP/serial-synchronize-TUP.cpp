//
// Created by sleepingmachine on 2022/4/9.
//

#include "serial-port-TUP.hpp"
extern std::mutex mutex2;

void SerialPortTUP::SerialSynchronize(int* sentData) {
    int mode,sentry,base;
    char ttyUSB_path[] = "/dev/ttyUSB0";//设置串口名称
    SerialPortTUP port(ttyUSB_path);//创建串口类对象
    port.initSerialPort();//串口初始化
    Mapdata data;
    int x,y;
    while (TRUE)
    {
        if (mutex2.try_lock()) {
            y = *sentData % 1000;
            x = (*sentData - y)/1000;
            mutex2.unlock();
        }

        data = {6,0,x,y};

        port.TransformData(data);
        port.send();
        port.get_Mode(mode,sentry,base);
    }
}