//
// Created by sleepingmachine on 2022/4/9.
//

#include "serial-port-TUP.hpp"

void SerialPortTUP::SerialSynchronize() {
    int mode,sentry,base;
    char ttyUSB_path[] = "/dev/ttyUSB0";//设置串口名称
    SerialPortTUP port(ttyUSB_path);//创建串口类对象
    port.initSerialPort();//串口初始化
    Mapdata data;
    float x,y;
    while (TRUE)
    {
        data = {15,1,(float)x,(float)y};
        port.TransformData(data);
        port.send();
        // port.get_Mode(mode,sentry,base);
    }

}