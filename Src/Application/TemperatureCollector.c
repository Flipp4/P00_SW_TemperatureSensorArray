/*
 * TemperatureCollector.c
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#include "TemperatureCollector.h"
#include "../Drivers/MCP9808/TemperatureSensor_MCP9808.h"

typedef enum TemperatureCollectorState_t
{
	TempCollect_EntryState,
	TempCollect_Initialized,
	TempCollect_TemperatureReadRequest,
	TempCollect_Waiting,
	TempCollect_Error
}TemperatureCollectorState_t;

typedef struct kTempCollect_Data_t
{
	I2C_HandleTypeDef* hTranscieverHandle;
	uint8_t u8DeviceCount;
	bool bEnabledFlag;
	bool bScheduleMeasurement;
	TemperatureCollectorState_t eState;
	bool bStateReady;
	float fConvertedTemperature;

}kTempCollect_Data_t;

kTempCollect_Data_t kTemperatureData =
{
	.bEnabledFlag = false,
	.eState = TempCollect_EntryState,
};

void TempCollect_Operate()
{
	switch(kTemperatureData.eState)
	{
	case(TempCollect_EntryState):
		AssertError(); // Incorrect entry - before initialization
		break;
	case(TempCollect_Initialized):
		if(kTemperatureData.bScheduleMeasurement)
		{
			kTemperatureData.eState = TempCollect_TemperatureReadRequest;
		}
		break;
	case(TempCollect_TemperatureReadRequest):
		kTemperatureData.bScheduleMeasurement = false;

		break;
	case(TempCollect_Waiting):
		break;
	default:
	break;
	}

}

void TempCollect_Initialize()
{
	kTemperatureData.eState = TempCollect_Initialized;
	kTemperatureData.bEnabledFlag = true;
}
void TempCollect_RetrieveResult(TemperatureData_t *sTemperatureData);
void TempCollect_ScheduleMeasurement()
{
	if(kTemperatureData.bScheduleMeasurement)
	{
		AssertError(); // Overlap of requests;
	}
	else
	{
		kTemperatureData.bScheduleMeasurement = true;
	}
}
