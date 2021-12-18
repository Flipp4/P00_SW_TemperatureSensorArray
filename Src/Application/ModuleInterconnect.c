/*
 * ModuleInterconnect.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#include "ModuleInterconnect.h"
#include "EventSystem.h"
#include "DataCommon.h"

void CallForTransmissionEvent()
{
	EventSystem_Signalize(Event_DataReadyToTransmit);
}
