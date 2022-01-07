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
	EventSystem_Signalize(eEvent_DataReadyToTransmit);
}

void CallForUSBConnection()
{
	EventSystem_Signalize(eEvent_USBConnected);
}
void CallForUSBDisonnection()
{
	EventSystem_Signalize(eEvent_USBDisconnected);
}

void CallForAverageAddition()
{
	EventSystem_Signalize(eEvent_DataReadyForAverage);
}

void CallForSensorReset()
{
	EventSystem_Signalize(eEvent_ResetSensors);
}

void CallForErrorSignalize_Supervisor()
{
	EventSystem_Signalize(eEvent_ErrorSupervisor);
}

void CallForErrorSignalize_Sensor()
{
	EventSystem_Signalize(eEvent_SignalizeSensorError);
}
