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
#include "stdint-gcc.h"
#include "includes.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define DIG1_Pin GPIO_PIN_14
#define DIG1_GPIO_Port GPIOC
#define SEG_A_Pin GPIO_PIN_15
#define SEG_A_GPIO_Port GPIOC
#define DIG3_Pin GPIO_PIN_0
#define DIG3_GPIO_Port GPIOA
#define SEG_B_Pin GPIO_PIN_1
#define SEG_B_GPIO_Port GPIOA
#define DIG4_Pin GPIO_PIN_2
#define DIG4_GPIO_Port GPIOA
#define SEG_G_Pin GPIO_PIN_3
#define SEG_G_GPIO_Port GPIOA
#define SEG_C_Pin GPIO_PIN_4
#define SEG_C_GPIO_Port GPIOA
#define SEG_DP_Pin GPIO_PIN_5
#define SEG_DP_GPIO_Port GPIOA
#define SEG_D_Pin GPIO_PIN_6
#define SEG_D_GPIO_Port GPIOA
#define SEG_E_Pin GPIO_PIN_7
#define SEG_E_GPIO_Port GPIOA
#define DHT11_DATA_Pin GPIO_PIN_8
#define DHT11_DATA_GPIO_Port GPIOA
#define DIG2_Pin GPIO_PIN_11
#define DIG2_GPIO_Port GPIOA
#define SEG_F_Pin GPIO_PIN_12
#define SEG_F_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
