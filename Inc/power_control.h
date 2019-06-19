/*
 * power_control.h
 *
 *  Created on: Jun 18, 2019
 *      Author: georg
 */

/* INCLUDES */
#include "main.h"

#ifndef INC_POWER_CONTROL_H_
#define INC_POWER_CONTROL_H_

#define DISABLE_2_PIN 	GPIO_PIN_13
#define DISABLE_2_PORT 	GPIOB
#define DISABLE_1_PIN 	GPIO_PIN_15
#define DISABLE_1_PORT 	GPIOA

#define __ENABLE_PWM_1() HAL_GPIO_WritePin(DISABLE_1_PORT, DISABLE_1_PIN, 0);
#define __DISABLE_PWM_1() HAL_GPIO_WritePin(DISABLE_1_PORT, DISABLE_1_PIN, 1);
#define __ENABLE_PWM_2() HAL_GPIO_WritePin(DISABLE_2_PORT, DISABLE_2_PIN, 0);
#define __DISABLE_PWM_2() HAL_GPIO_WritePin(DISABLE_2_PORT, DISABLE_2_PIN, 1);

void testPWM(void);

#endif /* INC_POWER_CONTROL_H_ */
