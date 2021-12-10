/*
 * DataHandler.c
 *
 *  Created on: Dec 9, 2021
 *      Author: Filip
 */

#include "DataHandler.h"

/*
 * Definition of how much measurements should fit into single measurement save cell
 * Eg. if application collect data from 16 sensors at single time moment (assumed)
 * then width shall be equal to 16
 */

#define dMemoryWidth 16
#define dMemoryLength 8
#define dMemoryPagesCount 2

typedef struct MeasurementEntry_t
{
	uint32_t u16Timestamp;
	float fMeasurementArray[dMemoryLength][dMemoryWidth];
	bool bAlreadySent;
}MeasurementEntry_t;

typedef struct DataHandler_t
{
	bool bEnabled;
	MeasurementEntry_t kMeasurementMemory[dMemoryPagesCount];
	uint8_t u8ActiveMemoryPage;
}DataHandler_t;

static DataHandler_t kDataHandler;

void DataHandler_Initialize()
{
	DataHandler_Reset();
	kDataHandler.bEnabled = true;

}
void DataHandler_Reset()
{
	for(uint8_t u8PageIdx = 0; u8PageIdx < dMemoryPagesCount; u8PageIdx++)
	{
		for(uint8_t u8LengthIdx = 0; u8LengthIdx < dMemoryLength; u8LengthIdx++)
		{
			kDataHandler.kMeasurementMemory[u8PageIdx].bAlreadySent = false;

			for(uint8_t u8WidthIdx = 0; u8WidthIdx < dMemoryWidth; u8WidthIdx++)
			{
				kDataHandler.kMeasurementMemory[u8PageIdx].fMeasurementArray[u8LengthIdx][u8WidthIdx] = 0;
			}
		}
	}

}
void DataHandler_OpenNewMeasurement( uint32_t u32TimeStamp )
{

}
void DataHandler_StoreMeasurement( float fNewMeasurement )
{

}
