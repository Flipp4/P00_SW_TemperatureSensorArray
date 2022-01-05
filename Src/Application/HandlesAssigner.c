/*
 * HandlesAssigner.c
 *
 *  Created on: 29 gru 2021
 *      Author: Filip
 */
#include "HandlesAssigner.h"

#include "../Application/Application.h"

typedef struct HandleAssignerData_t
{
	ADC_HandleTypeDef 	*phADC1;
	I2C_HandleTypeDef 	*phI2C1;
	I2C_HandleTypeDef 	*phI2C2;
	RTC_HandleTypeDef 	*phRTC;
	SD_HandleTypeDef 	*phSD;
	TIM_HandleTypeDef 	*phTIM2;
	TIM_HandleTypeDef 	*phTIM5;
	UART_HandleTypeDef	*phUART1;
	bool bEnabled;
}HandleAssignerData_t;

static HandleAssignerData_t kHandleAssignerData;

void HandlesAssigner_ShareHandle(void * phHandle, HandleType_t eHandleDeviceType)
{
	switch(eHandleDeviceType)
	{
		case (eHandle_TIM2):
			kHandleAssignerData.phTIM2 = phHandle;
			break;
		case (eHandle_TIM5):
			kHandleAssignerData.phTIM5 = phHandle;
			break;
		case (eHandle_I2C1):
			kHandleAssignerData.phI2C1 = phHandle;
			break;
		case (eHandle_I2C2):
			kHandleAssignerData.phI2C2 = phHandle;
			break;
		case (eHandle_RTC):
			kHandleAssignerData.phRTC = phHandle;
			break;
		case (eHandle_SD):
			kHandleAssignerData.phSD = phHandle;
			break;
		case (eHandle_ADC):
			kHandleAssignerData.phADC1 = phHandle;
			break;
		case (eHandle_UART1):
			kHandleAssignerData.phUART1 = phHandle;
			break;
		default:
			AssertError(eAppError_HALHandleAssignmentError);
			break;
	}
}

void* HandlesAssigner_GetHandle(HandleType_t eHandleDeviceType)
{
	void * phHandle;
	switch(eHandleDeviceType)
	{
		case (eHandle_TIM2):
			phHandle = kHandleAssignerData.phTIM2;
			break;
		case (eHandle_TIM5):
			phHandle = kHandleAssignerData.phTIM5;
			break;
		case (eHandle_I2C1):
			phHandle = kHandleAssignerData.phI2C1;
			break;
		case (eHandle_I2C2):
			phHandle = kHandleAssignerData.phI2C2;
			break;
		case (eHandle_RTC):
			phHandle = kHandleAssignerData.phRTC;
			break;
		case (eHandle_SD):
			phHandle = kHandleAssignerData.phSD;
			break;
		case (eHandle_ADC):
			phHandle = kHandleAssignerData.phADC1;
			break;
		case (eHandle_UART1):
			phHandle = kHandleAssignerData.phUART1;
			break;
		default:
			AssertError(eAppError_HALHandleAssignmentError);
			break;
	}
	return phHandle;
}
