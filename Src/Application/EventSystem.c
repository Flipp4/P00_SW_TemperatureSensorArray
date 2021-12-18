/*
 * EventSystem.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#include "EventSystem.h"
#include "Application.h"
#include "../Communication/CommunicationManager.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct EventData_t
{
	bool bInitalized;
	uint32_t u32EventRegister;
}EventData_t;

static EventData_t kEventData;

void EventSystem_Initialize()
{
	kEventData.bInitalized = true;
}
void EventSystem_HandleEvent()
{
	uint32_t u32EventCode = 0;

	u32EventCode = (uint32_t)Event_DataReadyToTransmit;

	if( (kEventData.u32EventRegister & u32EventCode) == u32EventCode )
	{
		ComManager_ArmTransmission();
		kEventData.u32EventRegister &= ~(u32EventCode);
	}
}

void EventSystem_Signalize(Event_t eEvent)
{
	uint32_t u32EventCode = (uint32_t)eEvent;

	if(kEventData.bInitalized)
	{
		if( (kEventData.u32EventRegister & u32EventCode) == u32EventCode )
		{
			AssertError(AppError_EventOverlap); // Event already set, before handling it
		}
		else
		{
			kEventData.u32EventRegister |= u32EventCode; // Set bit in register according to the event code
		}
	}
}
