/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "io_interface.h"
#include "power_control.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IO4_Pin GPIO_PIN_13
#define IO4_GPIO_Port GPIOC
#define IO3_Pin GPIO_PIN_14
#define IO3_GPIO_Port GPIOC
#define IO2_Pin GPIO_PIN_15
#define IO2_GPIO_Port GPIOC
#define LOAD_SENSE_B_Pin GPIO_PIN_0
#define LOAD_SENSE_B_GPIO_Port GPIOA
#define LOAD_SENSE_A_Pin GPIO_PIN_1
#define LOAD_SENSE_A_GPIO_Port GPIOA
#define CURRENT_SENSOR_Pin GPIO_PIN_2
#define CURRENT_SENSOR_GPIO_Port GPIOA
#define ANALOG_IN_Pin GPIO_PIN_3
#define ANALOG_IN_GPIO_Port GPIOA
#define DAC_OUT3_Pin GPIO_PIN_4
#define DAC_OUT3_GPIO_Port GPIOA
#define DAC_OUT2_Pin GPIO_PIN_5
#define DAC_OUT2_GPIO_Port GPIOA
#define DAC_OUT1_Pin GPIO_PIN_6
#define DAC_OUT1_GPIO_Port GPIOA
#define VOLTAGE_SENSE_Pin GPIO_PIN_7
#define VOLTAGE_SENSE_GPIO_Port GPIOA
#define V_THERM_Pin GPIO_PIN_0
#define V_THERM_GPIO_Port GPIOB
#define CURRENT_REF_Pin GPIO_PIN_1
#define CURRENT_REF_GPIO_Port GPIOB
#define FAN_OFF_Pin GPIO_PIN_12
#define FAN_OFF_GPIO_Port GPIOB
#define DISABLE_HB2_Pin GPIO_PIN_13
#define DISABLE_HB2_GPIO_Port GPIOB
#define DISABLE_HB1_Pin GPIO_PIN_15
#define DISABLE_HB1_GPIO_Port GPIOA
#define LED_GREEN2_Pin GPIO_PIN_3
#define LED_GREEN2_GPIO_Port GPIOB
#define LED_GREEN1_Pin GPIO_PIN_4
#define LED_GREEN1_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOB
#define IO1_Pin GPIO_PIN_7
#define IO1_GPIO_Port GPIOB
#define USB_NRST_Pin GPIO_PIN_9
#define USB_NRST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
