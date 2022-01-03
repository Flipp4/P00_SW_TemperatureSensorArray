/*
 * Filters.c
 *
 *  Created on: 3 sty 2022
 *      Author: Filip
 */

#include "Filters.h"

#include "../Application/Application.h"

#include "../Drivers/Sensors/TemperatureSensor_ArrayData.h"

typedef struct AverageSignalChannel_t
{
	float fCurrentValue;
	uint16_t u16SamplesCollected;
}AverageSignalChannel_t;

typedef struct SignalProcessingData_t
{
	bool bEnabled;
	bool bAverageCalculated;
	uint8_t u8ChannelCount;
	AverageSignalChannel_t kAverageChannels[dMaximumChannels];
	float fAverageRegister[dMaximumChannels];

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
		AssertError(AppError_SIgnalProcessingError);
	}
	else
	{
		kSignalProcessingData.kAverageChannels[u8Channel].fCurrentValue += fNewData;
		kSignalProcessingData.kAverageChannels[u8Channel].u16SamplesCollected++;
	}
}

void SignalProcessing_CalculateAverage()
{
	for(uint8_t u8Idx = 0; u8Idx < dMaximumChannels; u8Idx++)
	{
		kSignalProcessingData.fAverageRegister[u8Idx] = kSignalProcessingData.kAverageChannels[u8Idx].fCurrentValue / kSignalProcessingData.kAverageChannels[u8Idx].u16SamplesCollected;
	}
	kSignalProcessingData.bAverageCalculated = true;
}

float* SignalProcessing_ReadAverage()
{
	SignalProcessing_ResetChannels();
	return kSignalProcessingData.fAverageRegister;
}

static void SignalProcessing_ResetChannels()
{
	for(uint8_t u8Idx = 0; u8Idx < dMaximumChannels; u8Idx++)
	{
		kSignalProcessingData.kAverageChannels[u8Idx].fCurrentValue = 0;
		kSignalProcessingData.kAverageChannels[u8Idx].u16SamplesCollected = 0;
	}
	kSignalProcessingData.bAverageCalculated = false;
}
