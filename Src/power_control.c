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
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

uint32_t analog_in_raw = 0;
uint32_t current_sensor_raw = 0;
uint32_t result_count = 0;

ADC_HandleTypeDef hadc1;

void UpdateControlLoop(void){

	uint32_t analog_in_raw;
	uint32_t current_sense_raw;
	float pwm_output;

	analog_in_raw = ADC1_buffer[3];
	current_sense_raw = ADC1_buffer[2];

	pwm_output = (((float)analog_in_raw - (float)current_sense_raw))/500 + 0.5f;
	pwm_output = min(1.0f, pwm_output);
	pwm_output = max(0.0f, pwm_output);
	//pwm_output = 0.0f;

	setPWM1(pwm_output);
	setPWM2(pwm_output);

	__ENABLE_HB1();
	__ENABLE_HB2();

	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);

}

void testPWM(void){
/* Test routine for testing complementary PWM output */

	__ENABLE_HB1();
	__ENABLE_HB2();

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 100);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 100);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 300);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 300);

	__DISABLE_HB1();
	__DISABLE_HB2();
}

/* setPWMx(float input) - Set the duty cycle of a half bridge
 *
 * Set the PWM duty cycle according to the float input value.
 * The value applies to Q3 and Q6 so a value of 1 means Q3 and Q6 will be on permanently
 * A value of 0 means that Q4 and Q5 are on permanently.
 *
*/
void setPWM1(float input){
	uint16_t ARR_value = __HAL_TIM_GET_AUTORELOAD(&htim16);
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, input*ARR_value);
}

void setPWM2(float input){
	uint16_t ARR_value = __HAL_TIM_GET_AUTORELOAD(&htim15);
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, input*ARR_value);
}

