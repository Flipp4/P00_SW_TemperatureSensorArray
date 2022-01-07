/*
 * Supervisor.c
 *
 *  Created on: 7 sty 2022
 *      Author: Filip
 */

#include <stdbool.h>
#include "Supervisor.h"
#include "../Application/Application.h"
#include "../Application/ModuleInterconnect.h"
#include "../Communication/USBTransmitter.h"
#include "../Application/HandlesAssigner.h"

#define dMinimumTicksA	( 1 )
#define dMinimumTicksB	( 1 )

typedef struct SupervisorData_t
{
	bool bEnabled;
	uint16_t u16TickCounterA;
	uint16_t u16TickCounterB;
	ADC_HandleTypeDef *phADC;

}SupervisorData_t;

static void Supervisor_ResetUSBDetection();

static SupervisorData_t kSupervisorData;

void Supervisor_Initialize()
{
	kSupervisorData.bEnabled = true;
	kSupervisorData.u16TickCounterA = 0;
	kSupervisorData.u16TickCounterB = 0;
	kSupervisorData.phADC = HandlesAssigner_GetHandle(eHandle_ADC);
}

void Supervisor_TickA()
{
	if(kSupervisorData.bEnabled)
	{
		kSupervisorData.u16TickCounterA++;
	}
}

void Supervisor_TickB()
{
	if(kSupervisorData.bEnabled)
	{
		kSupervisorData.u16TickCounterB++;
	}
}

void Supervisor_Verify()
{
	if(kSupervisorData.bEnabled)
	{
		if ( (kSupervisorData.u16TickCounterA <= dMinimumTicksA) && (kSupervisorData.u16TickCounterB <= dMinimumTicksB) )
		{
			Supervisor_ResetUSBDetection();
			CallForErrorSignalize_Supervisor();
		}
		kSupervisorData.u16TickCounterA = 0;
		kSupervisorData.u16TickCounterB = 0;
	}
}

static void Supervisor_ResetUSBDetection()
{
	ADC_ChannelConfTypeDef sConfig = {0};

	HAL_ADC_Stop_IT(kSupervisorData.phADC);
	USB_InitalizeTransmitterLogic();
	HAL_ADC_DeInit(kSupervisorData.phADC);
	HAL_ADC_Init(kSupervisorData.phADC);

	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(kSupervisorData.phADC, &sConfig);
}
