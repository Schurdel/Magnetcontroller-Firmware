/*
 * power_control.c
 *
 *  Created on: Jun 18, 2019
 *      Author: georg
 */
#include "main.h"
#include "power_control.h"

TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;

void testPWM(void){
/* Test routine for testing complementary PWM output */

	__ENABLE_PWM_1();
	__ENABLE_PWM_2();

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 200);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 300);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 2000);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 1000);

	__DISABLE_PWM_1();
	__DISABLE_PWM_2();
}

