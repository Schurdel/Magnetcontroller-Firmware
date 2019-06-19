/*
 * control_master.c
 *
 *  Created on: Jun 19, 2019
 *      Author: georg
 */

/* INCLUDES */
#include "main.h"


void Update24kHz(void){

	HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);

}
