/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint-gcc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* 定义USART接收时的不同状态 */
#define STATE_IDLE  0
#define STATE_GET_TYPE  1
#define STATE_GET_ADDR  2
#define STATE_GET_DATA  3
#define STATE_POKE_EXECUTION  4
#define STATE_PEEK_EXECUTION  5

/* 定义区分不同指令类别 */
#define TYPE_ERROR  0
#define TYPE_PEEK   1
#define TYPE_POKE   2

/* 从收到的前四个字节判断指令类型 */
#define __IS_PEEK_TYPE(__TYPE__)  (__TYPE__[0] == 'p') && (__TYPE__[1] == 'e') && \
                                  (__TYPE__[2] == 'e') && (__TYPE__[3] == 'k')
#define __IS_POKE_TYPE(__TYPE__)  (__TYPE__[0] == 'p') && (__TYPE__[1] == 'o') && \
                                  (__TYPE__[2] == 'k') && (__TYPE__[3] == 'e')
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t state;
uint8_t type;
uint8_t typestr[4];     /* 指令类型字符串 */
uint8_t addrstr[10];    /* addr字符串 */
uint8_t datastr[10];    /* data字符串 */

/* 错误类型反馈 */
const uint8_t err_message_II[] = "INVALID INSTRUCTION!";  /* error：无效指令类别 */
const uint8_t err_message_IA[] = "INVALID ADDR!";    /* error：无效地址 */     
const uint8_t err_message_ID[] = "INVALID DATA!";    /* error：无效数据 */  
const uint8_t confirm_message[] = "\nDONE! EVERYTHING IS OK!";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void peek_execution(void);
void poke_execution(void);
uint32_t str_to_int(uint8_t *str, uint8_t typ);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */
  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  state = STATE_IDLE;   /* 确保初始状态为IDLE */
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    switch (state)
    {
      /* IDLE状态，未收到任何数据 */
      case STATE_IDLE:
        if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == SET)
        {
          /* 收到数据，跳转下一状态*/
          state = STATE_GET_TYPE;
        }
      break;
      /* GET_TYPE状态，正在接收前四个字节 */
      case STATE_GET_TYPE:
        HAL_UART_Receive(&huart1, (uint8_t *)typestr, sizeof(typestr), 5);
        if (__IS_PEEK_TYPE(typestr))
        {
          type = TYPE_PEEK;
          state = STATE_GET_ADDR;
        }
        else if (__IS_POKE_TYPE(typestr))
        {
          type = TYPE_POKE;
          state = STATE_GET_ADDR;
        }
        else
        {
          /* 接收到的指令类型出错，返回IDLE状态 */
          state = STATE_IDLE;
          HAL_UART_Transmit(&huart1, (uint8_t *)err_message_II, sizeof(err_message_II), 5);
        }
      break;
      /* GET_ADDR状态，正在接收<addr>字节 */
      case STATE_GET_ADDR:
        HAL_UART_Receive(&huart1, (uint8_t *)addrstr, sizeof(addrstr), 5);
        if (type == TYPE_PEEK)
          /* 指令类型为peek，转入peek指令执行状态 */
          state = STATE_PEEK_EXECUTION;
        else 
          /* 指令类型为poke，转入接收<data>状态 */
          state = STATE_GET_DATA;
      break;
      /* GET_DATA状态，正在接收<data>字节 */
      case STATE_GET_DATA:
        HAL_UART_Receive(&huart1, (uint8_t *)datastr, sizeof(datastr), 5);
        state = STATE_POKE_EXECUTION;
      break;
      /* PEEK_EXECUTION状态，正在执行PEEK指令相应操作 */
      case STATE_PEEK_EXECUTION:
        peek_execution();
        state = STATE_IDLE;
      break;
      /* POKE_EXECUTION状态，正在执行POKE指令相应操作 */
      case STATE_POKE_EXECUTION:
        poke_execution();
        state = STATE_IDLE;
      break;

      default:
      break;
    }
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief peek指令操作，包括分离并转换addr的值、读出addr地址内存的数据并发送
  * @note 比如addr 0x00008000，读回来的是字符串"<00008000>"
  * @retval None
  */
void peek_execution(void)
{
  uint32_t addr, data;
  uint8_t i, itmp, tx[10];
  if ((addr = str_to_int(addrstr, 1)) != 0)
  {
    data = *((uint32_t *)addr);
    tx[0] = '0';
    tx[1] = 'x';
    for (i = 0; i < 8; i++)
    {
      /* 采用移位的方式得到data的每一位，并存入发送缓冲的数组中 */
      itmp = (uint8_t)((data << (4*i)) >> 28);
      tx[i+2] = (itmp < 10) ? (itmp + '0') : (itmp + 'a' - 10);
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

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
