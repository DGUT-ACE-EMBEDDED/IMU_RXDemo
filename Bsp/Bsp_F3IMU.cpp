//
// Created by 16771 on 2023/6/6.
//

#include <cstdlib>
#include "Bsp_F3IMU.h"


//Bsp_F3IMU::Bsp_F3IMU(UART_HandleTypeDef *imuUartHandler) : IMU_UartHandler(imuUartHandler) {
//    Gyro_Rx_Buff = (unsigned char *) malloc(sizeof(unsigned char) * Gyro_Rx_Buffer_Num)
//
//            // ʹ��DMA���ڽ���
//            SET_BIT(imuUartHandler->Instance->CR3, USART_CR3_DMAR);
//    // ʹ�ܿ����ж�
//    __HAL_UART_ENABLE_IT(imuUartHandler, UART_IT_IDLE);
//    //    //����DMA���䣬������1�����ݰ��˵�recvive_buff��
//    //    HAL_UART_Receive_DMA(&huart1, sbus_rx_buf[0], 36 );
//    // ʧЧDMA
//    __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
//    while (imuUartHandler->hdmarx->Instance->CR & DMA_SxCR_EN) {
//        __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
//    }
//    imuUartHandler->hdmarx->Instance->PAR = (uint32_t) & (imuUartHandler->Instance->DR);
//    // �ڴ滺����1
//    imuUartHandler->hdmarx->Instance->M0AR = (uint32_t)(Gyro_Rx_Buff[0]);
//    // �ڴ滺����2
//    imuUartHandler->hdmarx->Instance->M1AR = (uint32_t)(Gyro_Rx_Buff[1]);
//    // ���ݳ���
//    imuUartHandler->hdmarx->Instance->NDTR = Gyro_Rx_Buffer_Num;
//    // ʹ��˫������
//    SET_BIT(imuUartHandler->hdmarx->Instance->CR, DMA_SxCR_DBM);
//    // ʹ��DMA
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

    // ʹ��DMA���ڽ���
    SET_BIT(imuUartHandler->Instance->CR3, USART_CR3_DMAR);
    // ʹ�ܿ����ж�
    __HAL_UART_ENABLE_IT(imuUartHandler, UART_IT_IDLE);
    //    //����DMA���䣬������1�����ݰ��˵�recvive_buff��
    //    HAL_UART_Receive_DMA(&huart1, sbus_rx_buf[0], 36 );
    // ʧЧDMA
    __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
    while (imuUartHandler->hdmarx->Instance->CR & DMA_SxCR_EN) {
        __HAL_DMA_DISABLE(imuUartHandler->hdmarx);
    }
    imuUartHandler->hdmarx->Instance->PAR = (uint32_t) & (imuUartHandler->Instance->DR);
    // �ڴ滺����1
    imuUartHandler->hdmarx->Instance->M0AR = (uint32_t)(Gyro_Rx_Buff[0]);
    // �ڴ滺����2
    imuUartHandler->hdmarx->Instance->M1AR = (uint32_t)(Gyro_Rx_Buff[1]);
    // ���ݳ���
    imuUartHandler->hdmarx->Instance->NDTR = Gyro_Rx_Buffer_Num;
    // ʹ��˫������
    SET_BIT(imuUartHandler->hdmarx->Instance->CR, DMA_SxCR_DBM);
    // ʹ��DMA
    __HAL_DMA_ENABLE(imuUartHandler->hdmarx);

}

bool Bsp_F3IMU::IMU_Decode(volatile const uint8_t *pData) {

    return false;
}
