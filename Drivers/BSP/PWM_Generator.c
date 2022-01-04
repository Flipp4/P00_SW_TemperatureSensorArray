/*
 * PWM_Generator.c
 *
 *  Created on: Jan 4, 2022
 *      Author: Filip
 */

#include <stdbool.h>
#include <stdint.h>
#include "PWM_Generator.h"
#include "../Src/Application/HandlesAssigner.h"

typedef struct PWMGenerator_t
{
	bool bEnabled;
	uint16_t u16CurrentPulseWidth;
	TIM_HandleTypeDef *phTIMhandle;
	float fPeriod;
	bool bDirectionUp;
	uint16_t u16Ticks;
}PWMGenerator_t;

static PWMGenerator_t PWMGeneratorData;

void PWMGenerator_Initialize()
{
	PWMGeneratorData.bEnabled = true;
	PWMGeneratorData.phTIMhandle = HandlesAssigner_GetHandle(eHandle_TIM5);
	PWMGeneratorData.u16CurrentPulseWidth = 0;
	PWMGeneratorData.bDirectionUp = true;
	PWMGeneratorData.u16Ticks = 0;
}

void PWMGenerator_RecalculatePWM()
{
	if(PWMGeneratorData.bDirectionUp)
	{
		PWMGeneratorData.fPeriod += dStepPerUpdatePerHalfPeriod;
	}
	else
	{
		PWMGeneratorData.fPeriod -= dStepPerUpdatePerHalfPeriod;
	}
	PWMGeneratorData.u16CurrentPulseWidth = (uint16_t)PWMGeneratorData.fPeriod;

	if(PWMGeneratorData.u16Ticks++ >= dUpdatesPerHalfPeriod)
	{
		PWMGeneratorData.u16Ticks = 0;
		if ( PWMGeneratorData.bDirectionUp )
		{
			PWMGeneratorData.bDirectionUp = false;
			PWMGeneratorData.fPeriod = 50.0;
		}
		else
		{
			PWMGeneratorData.bDirectionUp = true;
			PWMGeneratorData.fPeriod = 0.0;
		}
	}

}
void PWMGenerator_TurnPWMTimerOn()
{
	if(PWMGeneratorData.bEnabled)
	{
//		HAL_TIM_Base_Start(PWMGeneratorData.phTIMhandle);
		HAL_TIM_PWM_Start_IT(PWMGeneratorData.phTIMhandle, TIM_CHANNEL_4);
	}
}

void PWMGenerator_ApplyNewWidth()
{
	if(PWMGeneratorData.bEnabled)
	{
		__HAL_TIM_SET_COMPARE(PWMGeneratorData.phTIMhandle, TIM_CHANNEL_4, PWMGeneratorData.u16CurrentPulseWidth );
	}
}
