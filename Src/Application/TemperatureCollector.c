/*
 * TemperatureCollector.c
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#include "TemperatureCollector.h"
#include "../Drivers/MCP9808/TemperatureSensor_MCP9808.h"
#include "Application.h"

typedef enum TemperatureCollectorState_t
{
	TempCollect_EntryState,
	TempCollect_Initialized,
	TempCollect_TemperatureReadRequest,
	TempCollect_ProcessData,
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
	bool bStateReady[2];
	float fConvertedTemperature;
	uint16_t u16ArrayASensorIndex;
	uint16_t u16ArrayBSensorIndex;

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
			kTemperatureData.u16ArrayASensorIndex = 0;
			kTemperatureData.u16ArrayBSensorIndex = 0;
		}
		break;
	case(TempCollect_TemperatureReadRequest):
		kTemperatureData.bScheduleMeasurement = false;
		if(kTemperatureData.u16ArrayASensorIndex < MCP9808_I2CA_DeviceCount)
		{
			MCP9808_Read(&kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex]);

		}
		if(kTemperatureData.u16ArrayBSensorIndex < MCP9808_I2CB_DeviceCount)
		{
			MCP9808_Read(&kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex]);

		}
		kTemperatureData.eState = TempCollect_Waiting;
		break;
	case(TempCollect_Waiting):
		if(kTemperatureData.bStateReady[0] && kTemperatureData.bStateReady[1])
		{
			kTemperatureData.eState = TempCollect_ProcessData;
		}
		break;
	case(TempCollect_ProcessData):
		MCP9808_DecodeTemperature(&kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex]);
		MCP9808_DecodeTemperature(&kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex]);

		kTemperatureData.u16ArrayASensorIndex++;
		kTemperatureData.u16ArrayBSensorIndex++;

		if ( ( kTemperatureData.u16ArrayASensorIndex < MCP9808_I2CA_DeviceCount )
		  && ( kTemperatureData.u16ArrayBSensorIndex < MCP9808_I2CB_DeviceCount ) )
		{
			kTemperatureData.eState = TempCollect_TemperatureReadRequest;
		}
		else
		{
			kTemperatureData.eState = TempCollect_Initialized;
		}
		break;
	default:
		AssertError(); // Incorrect entry
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
