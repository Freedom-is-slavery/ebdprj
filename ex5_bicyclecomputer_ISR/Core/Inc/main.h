/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
struct TickCount  /* 计时结构，用于按键去抖动 */
{
  int16_t now;
  int16_t last;
  uint16_t interval;
};
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KeyRound_Pin GPIO_PIN_11
#define KeyRound_GPIO_Port GPIOA
#define KeyRound_EXTI_IRQn EXTI15_10_IRQn
#define KeyOutputMode_Pin GPIO_PIN_12
#define KeyOutputMode_GPIO_Port GPIOA
#define KeyOutputMode_EXTI_IRQn EXTI15_10_IRQn
/* USER CODE BEGIN Private defines */
#define KEY_DOWN 0
#define KEY_UP   1

#define OF_VELOCITY 1   //显示速度模式
#define OF_DISTANCE 0   //显示里程模式

#define USART_SBUF_DIGIT_D 14
#define USART_SBUF_DIGIT_V 14
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
