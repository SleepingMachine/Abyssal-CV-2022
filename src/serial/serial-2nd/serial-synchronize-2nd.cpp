//
// Created by sleepingmachine on 22-4-19.
//

#include "serial-port-2nd.hpp"

std::mutex mutex2;

void SerialPort2nd::SerialSynchronize2nd(int* sentData){
    char buff[6];
    const char *dev  = "/dev/ttyUSB0";
    SerialPort2nd myserial;
    int tempSendData,nread,nwrite;
    cout<<"serialPort Test"<<endl;
    myserial.OpenPort(dev);
    myserial.setup(19200,0,8,1,'N');
    //for (i=0;i<6;i++) buff[i]= 25;
    while (true)
    {
        if (mutex2.try_lock()) {
            tempSendData = *sentData;
            mutex2.unlock();
        }
        int hitPointData_y = tempSendData % 1000;
        int hitPointData_x = (tempSendData - hitPointData_y)/1000;
        //std::cout << hitPointData_x << " " << hitPointData_y << std::endl;

        buff[0] = 's';

        buff[1] = ((hitPointData_x >> 8) & 0xFF);
        buff[2] = ((hitPointData_x >> 0) & 0xFF);
        buff[3] = ((hitPointData_y >> 8) & 0xFF);
        buff[4] = ((hitPointData_y >> 0) & 0xFF);

        buff[5] = 'e';
        myserial.writeBuffer( buff, 6);
        myserial.readBuffer ( buff, 6);
        printf("%.*s",6,buff);
    }
}
