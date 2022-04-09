/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define Gas_Pin GPIO_PIN_3
#define Gas_GPIO_Port GPIOC
#define LED3pin1_Pin GPIO_PIN_0
#define LED3pin1_GPIO_Port GPIOA
#define LED3pin2_Pin GPIO_PIN_1
#define LED3pin2_GPIO_Port GPIOA
#define POWER_TX_Pin GPIO_PIN_2
#define POWER_TX_GPIO_Port GPIOA
#define POWER_RX_Pin GPIO_PIN_3
#define POWER_RX_GPIO_Port GPIOA
#define POT1_Pin GPIO_PIN_4
#define POT1_GPIO_Port GPIOA
#define POT2_Pin GPIO_PIN_5
#define POT2_GPIO_Port GPIOA
#define Tek1HLFB1_Pin GPIO_PIN_6
#define Tek1HLFB1_GPIO_Port GPIOA
#define Tek1HLFB2_Pin GPIO_PIN_7
#define Tek1HLFB2_GPIO_Port GPIOA
#define Current1R_Pin GPIO_PIN_4
#define Current1R_GPIO_Port GPIOC
#define Current1L_Pin GPIO_PIN_5
#define Current1L_GPIO_Port GPIOC
#define Current2R_Pin GPIO_PIN_0
#define Current2R_GPIO_Port GPIOB
#define Current2L_Pin GPIO_PIN_1
#define Current2L_GPIO_Port GPIOB
#define INH_Pin GPIO_PIN_7
#define INH_GPIO_Port GPIOE
#define Flipper_Front_A_Pin GPIO_PIN_10
#define Flipper_Front_A_GPIO_Port GPIOE
#define Flipper_Front_B_Pin GPIO_PIN_11
#define Flipper_Front_B_GPIO_Port GPIOE
#define Flipper_Back_A_Pin GPIO_PIN_12
#define Flipper_Back_A_GPIO_Port GPIOE
#define Flipper_Back_B_Pin GPIO_PIN_13
#define Flipper_Back_B_GPIO_Port GPIOE
#define TEK2PWM1_Pin GPIO_PIN_10
#define TEK2PWM1_GPIO_Port GPIOB
#define TEK2PWM2_Pin GPIO_PIN_11
#define TEK2PWM2_GPIO_Port GPIOB
#define TEK1PWM2_Pin GPIO_PIN_14
#define TEK1PWM2_GPIO_Port GPIOB
#define TEK1PWM1_Pin GPIO_PIN_15
#define TEK1PWM1_GPIO_Port GPIOB
#define TekEN_Pin GPIO_PIN_11
#define TekEN_GPIO_Port GPIOD
#define Tek2HLFB1_Pin GPIO_PIN_12
#define Tek2HLFB1_GPIO_Port GPIOD
#define Tek2HLFB1D13_Pin GPIO_PIN_13
#define Tek2HLFB1D13_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_15
#define LED2_GPIO_Port GPIOD
#define Dyna_TX_Pin GPIO_PIN_6
#define Dyna_TX_GPIO_Port GPIOC
#define Dyna_RX_Pin GPIO_PIN_7
#define Dyna_RX_GPIO_Port GPIOC
#define EN_ADM_Pin GPIO_PIN_8
#define EN_ADM_GPIO_Port GPIOC
#define XBEE_RX_Pin GPIO_PIN_9
#define XBEE_RX_GPIO_Port GPIOA
#define XBEE_TX_Pin GPIO_PIN_10
#define XBEE_TX_GPIO_Port GPIOA
#define XBEE_RST_Pin GPIO_PIN_11
#define XBEE_RST_GPIO_Port GPIOA
#define USRK1TX_Pin GPIO_PIN_10
#define USRK1TX_GPIO_Port GPIOC
#define USRK1RX_Pin GPIO_PIN_11
#define USRK1RX_GPIO_Port GPIOC
#define LOG_TX_Pin GPIO_PIN_12
#define LOG_TX_GPIO_Port GPIOC
#define LOG_RX_Pin GPIO_PIN_2
#define LOG_RX_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
