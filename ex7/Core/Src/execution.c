/**
  ******************************************************************************
  * 
  * @file           : execution.c
  * @brief          : 指令操作执行的函数库
  * 
  ******************************************************************************
  */


#include "execution.h"

const uint8_t confirm_message[] = "\nDONE!\n";
const uint8_t wait_xmodem_message[] = "\nReady for xmodem transmition!\n";

extern uint8_t addrstr[10];    /* addr字符串 */
extern uint8_t datastr[10];    /* data字符串 */
extern UART_HandleTypeDef huart1;

/**
  * @brief peek指令操作，包括分离并转换addr的值、读出addr地址内存的数据并发送
  * @note 比如addr 0x00008000，读回来的是字符串"<00008000>"
  * @retval None
  */
void peek_execution(void)
{
  uint32_t addr, data;
  uint8_t i, itmp, tx[] = "\ndata you peek: 0X        \n";
  if ((addr = str_to_int(addrstr, 1)) != 0)
  {
    data = *((uint32_t *)addr);
    for (i = 0; i < 8; i++)
    {
      /* 采用移位的方式得到data的每一位，并存入发送缓冲的数组中 */
      itmp = (uint8_t)((data << (4*i)) >> 28);
      tx[i + 19] = (itmp < 10) ? (itmp + '0') : (itmp + 'A' - 10);
    }
    HAL_UART_Transmit(&huart1, (uint8_t *)tx, sizeof(tx), 5);
    /* 发送指令操作成功信息，提示用户STATE将重新转入IDLE */
    HAL_UART_Transmit(&huart1, (uint8_t *)confirm_message, sizeof(confirm_message), 5);
  }
}

/**
  * @brief poke指令操作，包括分离并转换addr和data的值、向addr地址内存写入data，并发送回执信息
  * @retval None
  */
void poke_execution(void)
{
  uint32_t addr, data;

  if ((addr = str_to_int(addrstr, 1)) != 0)
  {
    /* 转换得到data值并写入对应内存中 */
    data = str_to_int(datastr, 2);
    *((uint32_t *)addr) = data;
    /* 发送指令操作成功信息，提示用户STATE将重新转入IDLE */
    HAL_UART_Transmit(&huart1, (uint8_t *)confirm_message, sizeof(confirm_message), 5);
  } 
}

/**
  * @brief load指令操作，包括分离并转换addr的值、接收一段数据保存在addr开始的RAM中
  * @retval None
  */
void load_execution(void)
{
    uint32_t addr;

    if ((addr = str_to_int(addrstr, 1)) != 0)
    {
      HAL_UART_Transmit(&huart1, (uint8_t *)wait_xmodem_message, sizeof(wait_xmodem_message), 5);
      xmodem_receive((uint8_t *)addr);
    }
}

/**
  * @brief run指令操作，包括分离并转换addr的值、运行从RAM地址addr开始的程序
  * @retval None
  */
void run_execution(void)
{
  volatile uint32_t jump_addr;    /* 要跳转的程序段所在的头地址 */
  void (*pFunc)(void);

  /* 检查栈顶地址是否合法 */
  if (((*(uint32_t *)(jump_addr = str_to_int(addrstr, 1))) & 0X2FFE0000) == 0X20000000)
  {
    __set_MSP(*(uint32_t *)jump_addr);    /* 所要跳转程序的主栈指针MSP的值存在程序起始地址中 */
    pFunc = (void (*) (void))(*((uint32_t *)(jump_addr + 4)));   /* 函数指针指向用户程序的复位中断向量 */
    HAL_DeInit();
    pFunc();    /* 跳转往用户程序的复位中断向量*/
  }
}
