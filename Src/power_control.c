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

float analog_in_raw = 0;
float current_sensor_raw = 0;

uint32_t analog_in_zero = 1965;					// Some measured default zero value for input adc
uint32_t current_sensor_zero = 2565; 			// Some measured default zero value for current sensor

ADC_HandleTypeDef hadc1;
DAC_HandleTypeDef hdac2;

void UpdateControlLoop(void){

	float analog_in_raw = 0;
	float current_sense_raw = 0;
	float pwm_output = 0;
	static float integrator = 0.0f;
	uint32_t sum_current = 0;
	uint32_t sum_analog = 0;

	// Form mean value of sensor data
	for(uint32_t k = 0; k<DAC1_CH1_BUFFER_LEN; k++){
		sum_current += DAC1_ch1_buffer[k];
		sum_analog += DAC1_ch2_buffer[k];
	}

	uint32_t current_mean = sum_current / DAC1_CH1_BUFFER_LEN;
	uint32_t analog_mean = sum_analog / DAC1_CH1_BUFFER_LEN;

	//Convert sensor data to voltage and current
	analog_in_raw = (float)((int32_t)analog_mean - (int32_t)analog_in_zero) * INPUT_VOLT * 3;      	// 3 Amps for each volt
	current_sense_raw = (float)((int32_t)current_mean - (int32_t)current_sensor_zero) * SENSOR_AMP; // Current in Amps

	//Determine pwm output
	if(HAL_GPIO_ReadPin(MODE_INPUT_GPIO_Port, MODE_INPUT_Pin)){
		// Control law - PI controller
		pwm_output = 0.5f + VOLT_PWM * K_P * (analog_in_raw-current_sense_raw)+ K_I*integrator*0;
	}
	else{
		// Directly use input for PWM
		pwm_output = VOLT_PWM * analog_in_raw;
	}


	// Conditional integration
	if(pwm_output < 1.0f && pwm_output > 0.0f){
		integrator += analog_in_raw-current_sense_raw;
	}

	// Limit the output to 99% to keep bootstrap cap charged...
	pwm_output = min(0.99f, pwm_output);
	pwm_output = max(0.01f, pwm_output);

	setPWM1(pwm_output);
	setPWM2(pwm_output);

	// Enable or disable the gate drivers
	if(HAL_GPIO_ReadPin(DISABLE_INPUT_GPIO_Port, DISABLE_INPUT_Pin)){
		__DISABLE_HB1();
		__DISABLE_HB2();
	}
	else{
		__ENABLE_HB1();
		__ENABLE_HB2();
	}

	// Send out PWM value via DAC
	uint32_t pwm_dac = pwm_output * 4095;
	HAL_DAC_SetValue(&hdac2, DAC_CHANNEL_1, DAC_ALIGN_12B_R, pwm_dac);

}

void zeroInput(void){

	uint32_t sum_input = 0;
	const uint32_t num = 10;

	// TODO: Do some more sophisticated filtering to get a proper zero value...
	for(uint32_t n = 0; n<num; n++){
		for(uint32_t k = 0; k<DAC1_CH2_BUFFER_LEN; k++){
			sum_input += DAC1_ch2_buffer[k];
		}
		HAL_Delay(100); //Delay 100ms
	}

	analog_in_zero = sum_input / (DAC1_CH2_BUFFER_LEN*num);
}

void zeroCurrent(void){

	uint32_t sum_current = 0;
	const uint32_t num = 10;

	// TODO: Do some more sophisticated filtering to get a proper zero value...
	for(uint32_t n = 0; n<num; n++){
		for(uint32_t k = 0; k<DAC1_CH1_BUFFER_LEN; k++){
			sum_current += DAC1_ch1_buffer[k];
		}
		HAL_Delay(100); //Delay 100ms
	}

	current_sensor_zero = sum_current / (DAC1_CH1_BUFFER_LEN*num);
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

