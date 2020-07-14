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

// Definitions
#define ADC1_NSAMPLES 8    								// Number of samples in each DMA buffer
#define ADC1_NCHANNELS 4								// Number of channels sampled in scan mode
#define ADC1_BUFFER_LEN ADC1_NSAMPLES*ADC1_NCHANNELS	// Total length of the ADC buffer written by DMA
#define DAC1_CH1_BUFFER_LEN ADC1_NSAMPLES 				// Total length of the DAC channel 1 buffer
#define DAC1_CH2_BUFFER_LEN ADC1_NSAMPLES 				// Total length of the DAC channel 2 buffer

#define ADC2_NSAMPLES 8									// Number of samples in each DMA buffer
#define ADC2_NCHANNELS 1 								// Number of channels sampled in scan mode
#define ADC2_BUFFER_LEN ADC2_NSAMPLES*ADC2_NCHANNELS    // Total length of the ADC buffer written by DMA
#define DAC2_BUFFER_LEN ADC2_NSAMPLES					// Total length of the DAC buffer

#define K_I 0.0058f 									// Integrator gain in V/(A * Sample)
#define K_P 5.4f 										// Proportional gain in V/A
#define SENSOR_AMP 1.0f/42.5f  							// Conversion factor for LSB to Ampere
#define INPUT_VOLT 2.5f*8.0f/4096.0f 					// Conversion factor for Analog Input LSB to Volts
#define VOLT_PWM 1.0f/24.0f/2 							// Conversion factor for Volts to PWM asymmetry


// Global variables for the ADC buffers
extern uint32_t ADC1_buffer[ADC1_BUFFER_LEN];			//Global variable for the ADC 1 buffer
extern uint32_t ADC2_buffer[ADC2_BUFFER_LEN]; 			//Global variable for the ADC 2 buffer
extern uint32_t DAC1_ch1_buffer[DAC1_CH1_BUFFER_LEN];
extern uint32_t DAC1_ch2_buffer[DAC1_CH2_BUFFER_LEN];


// Macro definition
#define __ENABLE_HB1() HAL_GPIO_WritePin(DISABLE_HB1_GPIO_Port, DISABLE_HB1_Pin, 0);
#define __DISABLE_HB1() HAL_GPIO_WritePin(DISABLE_HB1_GPIO_Port, DISABLE_HB1_Pin, 1);
#define __ENABLE_HB2() HAL_GPIO_WritePin(DISABLE_HB2_GPIO_Port, DISABLE_HB2_Pin, 0);
#define __DISABLE_HB2() HAL_GPIO_WritePin(DISABLE_HB2_GPIO_Port, DISABLE_HB2_Pin, 1);

// Function declaration
void testPWM(void);
void setPWM1(float input);
void setPWM2(float input);
void zeroInput(void);
void zeroCurrent(void);

void UpdateControlLoop(void);

#endif /* INC_POWER_CONTROL_H_ */
