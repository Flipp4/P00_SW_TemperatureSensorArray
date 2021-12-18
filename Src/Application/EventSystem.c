/*
 * EventSystem.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#include "EventSystem.h"
#include "Application.h"
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

}
void EventSystem_HandleEvent()
{

}


void EventSystem_Signalize(Event_t eEvent)
{
	uint32_t u32EventCode = (uint32_t)eEvent;

	if( (kEventData.u32EventRegister & u32EventCode) == u32EventCode )
	{
		AssertError(AppError_EventOverlap); // Event already set, before handling it
	}
	else
	{
		kEventData.u32EventRegister |= u32EventCode; // Set bit in register according to the event code
	}

}
