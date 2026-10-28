/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#define RED1_Pin GPIO_PIN_1
#define RED1_GPIO_Port GPIOA
#define YELLOW1_Pin GPIO_PIN_2
#define YELLOW1_GPIO_Port GPIOA
#define GREEN1_Pin GPIO_PIN_3
#define GREEN1_GPIO_Port GPIOA
#define RED2_Pin GPIO_PIN_4
#define RED2_GPIO_Port GPIOA
#define YELLOW2_Pin GPIO_PIN_5
#define YELLOW2_GPIO_Port GPIOA
#define GREEN2_Pin GPIO_PIN_6
#define GREEN2_GPIO_Port GPIOA
#define SEG1A_Pin GPIO_PIN_0
#define SEG1A_GPIO_Port GPIOB
#define SEG1B_Pin GPIO_PIN_1
#define SEG1B_GPIO_Port GPIOB
#define SEG1C_Pin GPIO_PIN_2
#define SEG1C_GPIO_Port GPIOB
#define SEG3C_Pin GPIO_PIN_10
#define SEG3C_GPIO_Port GPIOB
#define SEG3D_Pin GPIO_PIN_11
#define SEG3D_GPIO_Port GPIOB
#define SEG4A_Pin GPIO_PIN_12
#define SEG4A_GPIO_Port GPIOB
#define SEG4B_Pin GPIO_PIN_13
#define SEG4B_GPIO_Port GPIOB
#define SEG4C_Pin GPIO_PIN_14
#define SEG4C_GPIO_Port GPIOB
#define SEG4D_Pin GPIO_PIN_15
#define SEG4D_GPIO_Port GPIOB
#define BUT1_Pin GPIO_PIN_8
#define BUT1_GPIO_Port GPIOA
#define BUT2_Pin GPIO_PIN_9
#define BUT2_GPIO_Port GPIOA
#define BUT3_Pin GPIO_PIN_10
#define BUT3_GPIO_Port GPIOA
#define SEG1D_Pin GPIO_PIN_3
#define SEG1D_GPIO_Port GPIOB
#define SEG2A_Pin GPIO_PIN_4
#define SEG2A_GPIO_Port GPIOB
#define SEG2B_Pin GPIO_PIN_5
#define SEG2B_GPIO_Port GPIOB
#define SEG2C_Pin GPIO_PIN_6
#define SEG2C_GPIO_Port GPIOB
#define SEG2D_Pin GPIO_PIN_7
#define SEG2D_GPIO_Port GPIOB
#define SEG3A_Pin GPIO_PIN_8
#define SEG3A_GPIO_Port GPIOB
#define SEG3B_Pin GPIO_PIN_9
#define SEG3B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
