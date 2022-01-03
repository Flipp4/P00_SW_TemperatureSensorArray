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

void CallForUSBConnection()
{
	EventSystem_Signalize(Event_USBConnected);
}
void CallForUSBDisonnection()
{
	EventSystem_Signalize(Event_USBDisconnected);
}

void CallForAverageAddition()
{
	EventSystem_Signalize(Event_DataReadyForAverage);
}
