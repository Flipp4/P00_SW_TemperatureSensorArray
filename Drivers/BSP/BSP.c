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
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void ToggleLED_D()
{
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void OperateSensorPower_A (SensorState_t eState)
{
	if(eState == eSensor_On)
	{
		HAL_GPIO_WritePin(I2C1_VDD_GPIO_Port, I2C1_VDD_Pin, GPIO_PIN_RESET);
	}
	else if(eState == eSensor_Off)
	{
		HAL_GPIO_WritePin(I2C1_VDD_GPIO_Port, I2C1_VDD_Pin, GPIO_PIN_SET);
	}
}
void OperateSensorPower_B (SensorState_t eState)
{
	if(eState == eSensor_On)
	{
		HAL_GPIO_WritePin(I2C2_VDD_GPIO_Port, I2C2_VDD_Pin, GPIO_PIN_RESET);
	}
	else if(eState == eSensor_Off)
	{
		HAL_GPIO_WritePin(I2C2_VDD_GPIO_Port, I2C2_VDD_Pin, GPIO_PIN_SET);
	}
}

void TurnAllSensorOn()
{
	OperateSensorPower_A(eSensor_On);
	OperateSensorPower_B(eSensor_On);
}

void SetFirstDebugPinOn()
{
	HAL_GPIO_WritePin(PIN_0_GPIO_Port, PIN_0_Pin, GPIO_PIN_SET);
}
void SetFirstDebugPinOff()
{
	HAL_GPIO_WritePin(PIN_0_GPIO_Port, PIN_0_Pin, GPIO_PIN_RESET);
}

void SetSecondDebugPinOn()
{
	HAL_GPIO_WritePin(PIN_1_GPIO_Port, PIN_1_Pin, GPIO_PIN_SET);
}

void SetSecondDebugPinOff()
{
	HAL_GPIO_WritePin(PIN_1_GPIO_Port, PIN_1_Pin, GPIO_PIN_RESET);
}


