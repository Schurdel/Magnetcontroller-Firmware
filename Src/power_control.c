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

	__ENABLE_HB_1();
	__ENABLE_HB_2();

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 100);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 100);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 300);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 300);

	__DISABLE_HB_1();
	__DISABLE_HB_2();
}

void setPWM1(float input){
	uint16_t ARR_value = __HAL_TIM_GET_AUTORELOAD(&htim16);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, input*ARR_value);
}

void setPWM2(float input){
	uint16_t ARR_value = __HAL_TIM_GET_AUTORELOAD(&htim15);
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, input*ARR_value);
}


