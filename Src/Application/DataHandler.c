/*
 * DataHandler.c
 *
 *  Created on: Dec 9, 2021
 *      Author: Filip
 */

#include "DataHandler.h"
#include "Application.h"

/*
 * Definition of how much measurements should fit into single measurement save cell
 * Eg. if application collect data from 16 sensors at single time moment (assumed)
 * then width shall be equal to 16
 */

#define dMemoryWidth 		( 16 )
#define dMemoryLength 		( 8 )
#define dMemoryPagesCount 	( 2 )

typedef struct MeasurementEntry_t
{
	uint32_t u16Timestamp;
	float fMeasurementArray[dMemoryLength][dMemoryWidth];
	bool bAlreadySent;
	bool bHardSaved;
	bool bHardSaveRequest;
}MeasurementEntry_t;

typedef struct DataHandler_t
{
	bool bEnabled;
	MeasurementEntry_t kMeasurementMemory[dMemoryPagesCount];
	uint8_t u8ActiveMemoryPage;
	uint8_t u8LastMemoryPage;
	uint8_t u8WidthPointer;
	uint8_t u8LengthPointer;
	bool bPageFilled;
}DataHandler_t;

static DataHandler_t kDataHandler;

void DataHandler_Initialize()
{
	DataHandler_Reset();
	kDataHandler.bEnabled = true;

}
void DataHandler_Reset()
{
	kDataHandler.u8ActiveMemoryPage = 0;
	kDataHandler.u8LastMemoryPage = 0;
	kDataHandler.u8WidthPointer = 0;
	kDataHandler.u8LengthPointer = 0;
	kDataHandler.bPageFilled = false;

	for(uint8_t u8PageIdx = 0; u8PageIdx < dMemoryPagesCount; u8PageIdx++)
	{
		for(uint8_t u8LengthIdx = 0; u8LengthIdx < dMemoryLength; u8LengthIdx++)
		{
			kDataHandler.kMeasurementMemory[u8PageIdx].bAlreadySent = false;
			kDataHandler.kMeasurementMemory[u8PageIdx].bHardSaved = false;
			kDataHandler.kMeasurementMemory[u8PageIdx].bHardSaveRequest = false;

			for(uint8_t u8WidthIdx = 0; u8WidthIdx < dMemoryWidth; u8WidthIdx++)
			{
				kDataHandler.kMeasurementMemory[u8PageIdx].fMeasurementArray[u8LengthIdx][u8WidthIdx] = 0;
			}
		}
	}

}
void DataHandler_OpenNewMeasurement( uint32_t u32TimeStamp )
{

	if( kDataHandler.bEnabled )
	{
		kDataHandler.u8LengthPointer++;
		kDataHandler.u8WidthPointer = 0;

		if(kDataHandler.u8LengthPointer >= dMemoryLength)
		{
			kDataHandler.u8LengthPointer = 0;
			kDataHandler.kMeasurementMemory[kDataHandler.u8ActiveMemoryPage].bAlreadySent = false;
			kDataHandler.kMeasurementMemory[kDataHandler.u8ActiveMemoryPage].bHardSaveRequest = true;
			kDataHandler.kMeasurementMemory[kDataHandler.u8ActiveMemoryPage].bHardSaved = false;
			kDataHandler.kMeasurementMemory[kDataHandler.u8ActiveMemoryPage].u16Timestamp = u32TimeStamp;

			if( !kDataHandler.kMeasurementMemory[kDataHandler.u8ActiveMemoryPage].bHardSaved )
			{
				AssertError(AppError_DataLost); // Data not saved; possibly add timestamp to track lost data chunks
			}

			kDataHandler.u8LastMemoryPage = kDataHandler.u8ActiveMemoryPage;
			kDataHandler.u8ActiveMemoryPage++;
			if(kDataHandler.u8ActiveMemoryPage >= dMemoryPagesCount)
			{
				kDataHandler.u8ActiveMemoryPage = 0;
			}

		}
	}
	else
	{
		AssertError(AppError_DataHandlerUninitialized); // Call to DataHandler procedure before initialization
	}

}
void DataHandler_StoreMeasurement( float fNewMeasurement )
{
	uint8_t u8MemPage = kDataHandler.u8ActiveMemoryPage;
	uint8_t u8LenPtr = kDataHandler.u8LengthPointer;
	uint8_t u8WidPtr = kDataHandler.u8WidthPointer;

	if( kDataHandler.bEnabled )
	{

		kDataHandler.kMeasurementMemory[u8MemPage].fMeasurementArray[u8LenPtr][u8WidPtr] = fNewMeasurement;

		kDataHandler.u8WidthPointer++;

		if(kDataHandler.u8WidthPointer >= dMemoryWidth)
		{
			kDataHandler.u8WidthPointer--;
			AssertError(AppError_WidthOverstretched); // Width overstretched - no new measurement was called;
		}
	}
	else
	{
		AssertError(AppError_DataHandlerUninitialized); // Call to DataHandler procedure before initialization
	}
}

void DataHandler_Operate()
{
	if( kDataHandler.bEnabled )
	{

		if( kDataHandler.bPageFilled )
		{
			kDataHandler.kMeasurementMemory[kDataHandler.u8LastMemoryPage].bHardSaveRequest = true;
			// Call to save with SD card
		}

	}
	else
	{
		AssertError(AppError_DataHandlerUninitialized); // Call to DataHandler procedure before initialization
	}
}
