/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;

extern uint16_t tmp;
extern uint8_t dcnt;

extern uint8_t FlagOutputMode;        
extern uint8_t USART_SendBuf_D[18];
extern uint8_t USART_SendBuf_V[21];
extern struct TickCount TC_PA11, TC_PA12;
extern uint8_t RoundCount, LastRoundCount, Velocity;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  /* TIM3每隔1秒进1次中断 */
  /* 每秒计算当前时速 */
  Velocity = 36 * (RoundCount - LastRoundCount) / 10;
  LastRoundCount = RoundCount;
  /* 串口发里程数据 */
  if (FlagOutputMode == OF_DISTANCE)
  {
    /* 将里程转成ASCII码填入发送缓冲区 */
    tmp = RoundCount;
    dcnt = 0;
    USART_SendBuf_D[USART_SBUF_DIGIT_D] = 0 + 48;
    while(tmp != 0)
    {
      USART_SendBuf_D[USART_SBUF_DIGIT_D - (dcnt++)] = tmp % 10 + 48;
      tmp /= 10;
    }
    /* DMA传里程数据给串口 */
    HAL_UART_Transmit_DMA(&huart1, USART_SendBuf_D, sizeof(USART_SendBuf_D));
  }
  /* 串口发速度数据 */
  else if (FlagOutputMode == OF_VELOCITY)
  {
    /* 将速度转成ASCII码填入发送缓冲区 */
    tmp = Velocity;
    dcnt = 0;
    USART_SendBuf_V[USART_SBUF_DIGIT_V] = 0 + 48;
    USART_SendBuf_V[USART_SBUF_DIGIT_V-1] = ' ';
    while(tmp != 0)
    {
      USART_SendBuf_V[USART_SBUF_DIGIT_V - (dcnt++)] = tmp % 10 + 48;
      tmp /= 10;
    }
    /* DMA传速度数据给串口 */
    HAL_UART_Transmit_DMA(&huart1, USART_SendBuf_V, sizeof(USART_SendBuf_V));
  }
  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
  /* USER CODE END EXTI15_10_IRQn 0 */
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
  if (__HAL_GPIO_EXTI_GET_IT(KeyRound_Pin) != RESET)   
  {
    /* PA11模拟钢圈计数 */
    /* BEGIN */
    TC_PA11.last = __HAL_TIM_GET_COUNTER(&htim4);      //去抖动开始计时
    TC_PA11.now = TC_PA11.last;
    while((TC_PA11.interval = (TC_PA11.now >= TC_PA11.last) ? \
         (TC_PA11.now - TC_PA11.last) : (10000 + TC_PA11.now - TC_PA11.last)) <= 10)
    {
      TC_PA11.now = __HAL_TIM_GET_COUNTER(&htim4);
    }
    if(HAL_GPIO_ReadPin(KeyRound_GPIO_Port, KeyRound_Pin) == KEY_DOWN)
    {
      RoundCount++;
    }
    /* END */
    __HAL_GPIO_EXTI_CLEAR_IT(KeyRound_Pin);
  }
  else if (__HAL_GPIO_EXTI_GET_IT(KeyOutputMode_Pin) != RESET)   //PA12按键模式切换
  {
    /* PA12改变输出模式 */
    /* BEGIN */
    TC_PA12.last = __HAL_TIM_GET_COUNTER(&htim4);      //去抖动开始计时
    TC_PA12.now = TC_PA12.last;
    while((TC_PA12.interval = (TC_PA12.now >= TC_PA12.last) ? \
         (TC_PA12.now - TC_PA12.last) : (10000 + TC_PA12.now - TC_PA12.last)) <= 10)
    {
      TC_PA12.now = __HAL_TIM_GET_COUNTER(&htim4);
    }
    if(HAL_GPIO_ReadPin(KeyOutputMode_GPIO_Port, KeyOutputMode_Pin) == KEY_DOWN)
    {
      /* 输出状态标志取反 */
      FlagOutputMode = (~FlagOutputMode) & 0X01;
    }
    /* END */
    __HAL_GPIO_EXTI_CLEAR_IT(KeyOutputMode_Pin);
  }
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
