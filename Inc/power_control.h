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
#define ADC1_NSAMPLES 6									// Number of samples in each dma buffer
#define ADC1_NCHANNELS 4								// Number of channels sampled in scan mode
#define ADC1_BUFFER_LEN ADC1_NSAMPLES*ADC1_NCHANNELS	// Total length of the adc buffer written by DMA

extern uint32_t ADC1_buffer[ADC1_BUFFER_LEN];			//Global variable for the ADC buffer


// Macro definition
#define __ENABLE_HB1() HAL_GPIO_WritePin(DISABLE_HB1_GPIO_Port, DISABLE_HB1_Pin, 0);
#define __DISABLE_HB1() HAL_GPIO_WritePin(DISABLE_HB1_GPIO_Port, DISABLE_HB1_Pin, 1);
#define __ENABLE_HB2() HAL_GPIO_WritePin(DISABLE_HB2_GPIO_Port, DISABLE_HB2_Pin, 0);
#define __DISABLE_HB2() HAL_GPIO_WritePin(DISABLE_HB2_GPIO_Port, DISABLE_HB2_Pin, 1);

// Function declaration
void testPWM(void);
void setPWM1(float input);
void setPWM2(float input);

void Update24kHz(void);

#endif /* INC_POWER_CONTROL_H_ */
