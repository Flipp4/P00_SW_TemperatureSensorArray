/*
 * Filters.c
 *
 *  Created on: 3 sty 2022
 *      Author: Filip
 */

#include "Filters.h"

#include "../Application/Application.h"
#include "../Drivers/Sensors/TemperatureSensor_ArrayData.h"

#define dMaximumChannels ( Sensor_I2CA_DeviceCount + Sensor_I2CB_DeviceCount )

typedef struct AverageSignalChannel_t
{
	float fCurrentValue;
	uint16_t u16SamplesCollected;
}AverageSignalChannel_t;

typedef struct SignalProcessingData_t
{
	bool bEnabled;
	uint8_t u8ChannelCount;
	AverageSignalChannel_t kAverageChannels[dMaximumChannels];

}SignalProcessingData_t;

static SignalProcessingData_t kSignalProcessingData;

static void SignalProcessing_ResetChannels();

void SignalProcessing_Initialize(uint8_t u8Channels)
{
	kSignalProcessingData.bEnabled = true;
	kSignalProcessingData.u8ChannelCount = u8Channels;
}

void SignalProcessing_AddSampleToAverage(float fNewData, uint8_t u8Channel)
{
	if( u8Channel > kSignalProcessingData.u8ChannelCount )
	{
		AssertError();
	}

}

float* SignalProcessing_ReadAverage(uint8_t u8Channel)
{

	SignalProcessing_ResetChannels();
	return 0;
}

static void SignalProcessing_ResetChannels()
{

}
