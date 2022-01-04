/*
 * HandlesAssigner.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_HANDLESASSIGNER_H_
#define APPLICATION_HANDLESASSIGNER_H_

#include "../stm32f4xx_hal.h"

typedef enum HandleType_t
{
	eHandle_TIM2,
	eHandle_TIM5,
	eHandle_I2C1,
	eHandle_I2C2,
	eHandle_RTC,
	eHandle_SD,
	eHandle_ADC,
	eHandle_UART1
}HandleType_t;

void HandlesAssigner_ShareHandle(void * hHandle, HandleType_t eHandleDeviceType);
void* HandlesAssigner_GetHandle(HandleType_t eHandleDeviceType);


#endif /* APPLICATION_HANDLESASSIGNER_H_ */
