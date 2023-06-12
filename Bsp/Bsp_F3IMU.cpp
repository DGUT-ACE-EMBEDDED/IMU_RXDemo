//
// Created by 16771 on 2023/6/6.
//

#include <cstdlib>
#include "Bsp_F3IMU.h"


//Bsp_F3IMU::Bsp_F3IMU(UART_HandleTypeDef *imuUartHandler) : IMU_UartHandler(imuUartHandler) {
//    Gyro_Rx_Buff = (unsigned char *) malloc(sizeof(unsigned char) * Gyro_Rx_Buffer_Num)
//
//            // 使能DMA串口接收
//            SET_BIT(imuUartHandler->Instance->CR3, USART_CR3_DMAR);
//    // 使能空闲中断
//    __HAL_UART_ENABLE_IT(imuUartHandler, UART_IT_IDLE);
//    //    //设置DMA传输，将串口1的数据搬运到recvive_buff中
//    //    HAL_UART_Receive_DMA(&huart1, sbus_rx_buf[0], 36 );
//    // 失效DMA
//    __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
//    while (imuUartHandler->hdmarx->Instance->CR & DMA_SxCR_EN) {
//        __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
//    }
//    imuUartHandler->hdmarx->Instance->PAR = (uint32_t) & (imuUartHandler->Instance->DR);
//    // 内存缓冲区1
//    imuUartHandler->hdmarx->Instance->M0AR = (uint32_t)(Gyro_Rx_Buff[0]);
//    // 内存缓冲区2
//    imuUartHandler->hdmarx->Instance->M1AR = (uint32_t)(Gyro_Rx_Buff[1]);
//    // 数据长度
//    imuUartHandler->hdmarx->Instance->NDTR = Gyro_Rx_Buffer_Num;
//    // 使能双缓冲区
//    SET_BIT(imuUartHandler->hdmarx->Instance->CR, DMA_SxCR_DBM);
//    // 使能DMA
//    __HAL_DMA_ENABLE(imuUartHandler->hdmarx);
//}
Bsp_F3IMU::Bsp_F3IMU(UART_HandleTypeDef *imuUartHandler, int gyroRxBufferNum) : IMU_UartHandler(imuUartHandler),
                                                                                     Gyro_Rx_Buffer_Num(
                                                                                             gyroRxBufferNum) {

    Gyro_Rx_Buff = (unsigned char **) malloc(2 * sizeof(unsigned char *));
    if (Gyro_Rx_Buff == NULL) {
        isInit = false;
    }
    for(int i=0;i<2;i++) {
        Gyro_Rx_Buff[i] = (unsigned char *) malloc(gyroRxBufferNum * sizeof(unsigned char));
        if (Gyro_Rx_Buff[i] == NULL) {
            isInit = false;
        }
    }

    // 使能DMA串口接收
    SET_BIT(imuUartHandler->Instance->CR3, USART_CR3_DMAR);
    // 使能空闲中断
    __HAL_UART_ENABLE_IT(imuUartHandler, UART_IT_IDLE);
    //    //设置DMA传输，将串口1的数据搬运到recvive_buff中
    //    HAL_UART_Receive_DMA(&huart1, sbus_rx_buf[0], 36 );
    // 失效DMA
    __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
    while (imuUartHandler->hdmarx->Instance->CR & DMA_SxCR_EN) {
        __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
    }
    imuUartHandler->hdmarx->Instance->PAR = (uint32_t) & (imuUartHandler->Instance->DR);
    // 内存缓冲区1
    imuUartHandler->hdmarx->Instance->M0AR = (uint32_t)(Gyro_Rx_Buff[0]);
    // 内存缓冲区2
    imuUartHandler->hdmarx->Instance->M1AR = (uint32_t)(Gyro_Rx_Buff[1]);
    // 数据长度
    imuUartHandler->hdmarx->Instance->NDTR = Gyro_Rx_Buffer_Num;
    // 使能双缓冲区
    SET_BIT(imuUartHandler->hdmarx->Instance->CR, DMA_SxCR_DBM);
    // 使能DMA
    __HAL_DMA_ENABLE(imuUartHandler->hdmarx);

}

bool Bsp_F3IMU::IMU_Decode(volatile const uint8_t *pData) {

    return false;
}
