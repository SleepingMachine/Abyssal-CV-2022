//
// Created by sleepingmachine on 2022/4/9.
//

#ifndef ABYSSAL_CV_2022_SERIAL_CRC_TUP_HPP
#define ABYSSAL_CV_2022_SERIAL_CRC_TUP_HPP

#include <iostream>
#include <stdint.h>
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength, unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);

#endif //ABYSSAL_CV_2022_SERIAL_CRC_TUP_HPP
