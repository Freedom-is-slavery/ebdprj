/**
  ******************************************************************************
  * 
  * @file           : strconv.c
  * @brief          : 字符串和数字间格式转换
  * 
  ******************************************************************************
  */

#include "strconv.h"


const uint8_t err_message_IA[] = "INVALID ADDR!\n";    /* error：无效地址 */     
const uint8_t err_message_ID[] = "INVALID DATA!\n";    /* error：无效数据 */

extern UART_HandleTypeDef huart1;

/**
 * @brief 将字符串转换成数字
 * @param str 从PC端接收到的字符串
 * @param typ 要求转换的数值类型
 * @arg 1:addr ; 2:data
 * @retval 转换后的数值
 * @arg 0:转换出现错误(输入字符串不合规)
 */
uint32_t str_to_int(uint8_t *str, uint8_t typ)
{
  uint32_t tmp = 0;
  uint8_t i,ctmp,itmp;

  for (i = 1; i <= 8; i++)
  {
    ctmp = str[i];
    if (ctmp <= '9' && ctmp >= '0')
      itmp = ctmp - '0';
    else if (ctmp <= 'f' && ctmp >= 'a')
      itmp = ctmp - 'a' + 10;
    else if (ctmp <= 'F' && ctmp >= 'A')
      itmp = ctmp - 'A' + 10;
    else
    {
      /* 串口发送错误信息并直接返回 */
      if (typ == 1)
        HAL_UART_Transmit(&huart1, (uint8_t *)err_message_IA, sizeof(err_message_IA), 5);
      else if (typ == 2)
        HAL_UART_Transmit(&huart1, (uint8_t *)err_message_ID, sizeof(err_message_ID), 5);
      
      return 0;
    }
    tmp += (uint32_t)(itmp << (4*(8-i)));
  }
  return tmp;
}