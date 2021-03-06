/**
  ******************************************************************************
  * 
  * @file           : xmodem.c
  * @brief          : xmodem串口数据传输协议的函数库
  * 
  ******************************************************************************
  */

#include "xmodem.h"

#define SOH 0X01    /* Start of Header */
#define STX 0X02    /* Xmodem-1k Start of Header*/
#define EOT 0X04    /* End of Transmition */
#define ACK 0X06    /* Acknowledged */
#define NAK 0X15    /* Not Acknowledged */
#define CAN 0X18    /* Cancel the Transmition */
#define CTRLZ 0X1A  /* Fill the Blank */

#define BLOCKSIZE 132
#define DATASIZE  128 

extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

const uint8_t xmodem_done_message[] = "Xmodem Transmition Done!\n";
const uint8_t xmodem_error_message[] = "Xmodem Error!\n";

/**
 * @brief 启动xmodem接收
 * @param pbuf 存放接收到数据的缓冲区头指针
 **/
void xmodem_receive(uint8_t *pbuf)
{
    uint8_t Txback = NAK;
    uint8_t header, packnum, rpacknum, checksum; 
    do
    {
        HAL_Delay(3000);
        HAL_UART_Transmit(&huart1, &Txback, 1, 10);     /* 发送NAK来启动第一次接收 */
        while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
        HAL_Delay(1);
    }while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET);

    while (1)
    {
        /* 接收数据包头并判断是否为EOT */
        HAL_UART_Receive(&huart1, &header, 1, 20);
        if (header == EOT)
        {
            /* 发送ACK确认EOT完成传输 */
            Txback = ACK;
            HAL_UART_Transmit(&huart1, &Txback, 1, 5);
            while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
            HAL_Delay(500);
            /* 发送传输完成信息 */
            HAL_UART_Transmit(&huart1, (uint8_t *)xmodem_done_message, sizeof(xmodem_done_message), 5);
            while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
            break;
        }
        else if (header == SOH)
        {
            /* 接收包头的余下两个字节 */
            HAL_UART_Receive(&huart1, &packnum, 1, 20);
            HAL_UART_Receive(&huart1, &rpacknum, 1, 20);
            /* 接收数据部分 */
            HAL_UART_Receive(&huart1, pbuf, DATASIZE, 20);
            /* 接收校验和 */
            HAL_UART_Receive(&huart1, &checksum, 1, 20);
            if (calsum(pbuf, DATASIZE) == checksum)
            {
                Txback = ACK;
                HAL_UART_Transmit(&huart1, &Txback, 1, 5);
                while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
                pbuf += DATASIZE;
            }
            else
            {
                Txback = NAK;
                HAL_UART_Transmit(&huart1, &Txback, 1, 5);
                while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
            }
            while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET);
        }
        /* 无效包头，非SOH */
        else
        {
            HAL_UART_Transmit(&huart1, (uint8_t *)xmodem_error_message, sizeof(xmodem_error_message), 5);
            while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) == RESET);
            break;
        }    
    }
}

/**
 * @brief 计算8位累加和
 * @note 若接收方发送NAK来启动传输，则表明使用累加和校验
 * @param ptr 头数据指针
 * @param size 数据字节数
 * @retval 累加和
 **/
uint8_t calsum(const uint8_t *ptr, int16_t size)
{  
    uint8_t sum = 0;  
 
    while (--size >= 0)  
    {  
        sum += (uint8_t)(*ptr++);
    }

    return sum;  
}  

/**
 * @brief 计算16位CRC校验和
 * @note 若接收方发送字符'C'，则表明使用CRC校验
 * @param ptr 头数据指针
 * @param size 数据字节数
 **/
uint16_t calcrc(const uint8_t *ptr, int16_t size)
{  
    uint16_t crc;  
    uint8_t i;  
  
    crc = 0;  
    while (--size >= 0)  
    {  
        crc = crc ^ (int) *ptr++ << 8;  
        i = 8;  
        do  
        {  
            if (crc & 0x8000)  
                crc = crc << 1 ^ 0x1021;  
            else  
                crc = crc << 1;  
        } while (--i);  
    }
    return crc;  
}  

void xmodem_delay200us(void)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Start(&htim3);
    while (__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) == RESET);
    HAL_TIM_Base_Stop(&htim3);
    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
}
