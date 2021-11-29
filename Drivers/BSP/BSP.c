/*
 * BSP.c
 *
 *  Created on: 29 lis 2021
 *      Author: Filip
 */

#include "BSP.h"
#include "main.h"


void OperateLED_A (LEDState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	}
}
void OperateLED_B (LEDState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	}
}
void OperateLED_C (LEDState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	}
}
void OperateLED_D (LEDState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	}
}

void ToggleLED_B()
{
	HAL_GPIO_Toggle(LED1_GPIO_Port, LED1_Pin);
}

void OperateSensorPower_A (SensorState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(I2C1_VDD_GPIO_Port, I2C1_VDD_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(I2C1_VDD_GPIO_Port, I2C1_VDD_Pin, GPIO_PIN_RESET);
	}
}
void OperateSensorPower_B (SensorState_t eState)
{
	if(eState == eLED_On)
	{
		HAL_GPIO_WritePin(I2C2_VDD_GPIO_Port, I2C2_VDD_Pin, GPIO_PIN_SET);
	}
	else if(eState == eLED_Off)
	{
		HAL_GPIO_WritePin(I2C2_VDD_GPIO_Port, I2C2_VDD_Pin, GPIO_PIN_RESET);
	}
}



