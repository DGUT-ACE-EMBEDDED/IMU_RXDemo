//
// Created by 16771 on 2023/6/6.
//

#ifndef IMU_BSP_F3IMU_H
#define IMU_BSP_F3IMU_H
#include <usart.h>



class Bsp_F3IMU {
public:

    struct Euler_Angle{
        float pitch;
        float yaw;
        float roll;
    };

    float Total_Yaw;
    float Q[4];

    Bsp_F3IMU(UART_HandleTypeDef *imuUartHandler, int gyroRxBufferNum = 40);
    bool IMU_Decode(volatile const uint8_t *pData);
private:
    bool isInit = true;

    UART_HandleTypeDef *IMU_UartHandler;
    unsigned char Frame_Tail[4] = {0, 0, 0x80, 0x7F};
    int Gyro_Rx_Buffer_Num ;
    unsigned char **Gyro_Rx_Buff;

};


#endif //IMU_BSP_F3IMU_H
