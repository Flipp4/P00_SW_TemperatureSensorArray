/*
 * DataSaver.c
 *
 *  Created on: 3 sty 2022
 *      Author: Filip
 */

#include "DataSaver.h"
#include "Application.h"
#include "DataHandler.h"
#include "DataCommon.h"

#include "../Signal processing/Filters.h"

#include "../Communication/FrameAssembler.h"

#include "../Middlewares/Third_Party/FatFs/src/ff.h"

#include "../Inc/fatfs.h"

typedef enum DataSaverState_t
{
	DataSaverState_Wait,
	DataSaverState_AddToAverageSum,
	DataSaverState_CalculateAverage,
	DataSaverState_GetCurrentTime,
	DataSaverState_StoreAverage,
	DataSaverState_OpenFile,
	DataSaverState_CallSDSave,
	DataSaverState_CloseFile
}DataSaverState_t;

typedef struct DataSaver_t
{
	bool bEnabled;
	bool bAveragingPeriodElapsed;
	bool bNewDataAvailable;
	bool bDataInputFull;
	uint8_t u8CurrentSavingPage;
	uint8_t u8PreviousSavingPage;
	uint8_t u8SaveIndex;
	uint8_t u8SavingPage[dSavingPageCount][dSavingPageSize];
	uint8_t u8DataProcessingIndex;
	MemoryInterchange_t* pkMeasurementPointer;
	float* pfAveragePointer;
	uint16_t u16TickCounter;
	DataSaverState_t eState;
	FRESULT kCardResult;
}DataSaver_t;

static DataSaver_t kDataSaver;
static WORD kWordCount;

void DataSaver_Initialize()
{
	kDataSaver.bEnabled = true;
	kDataSaver.u8CurrentSavingPage = 0;
	kDataSaver.u8PreviousSavingPage = 0;
	kDataSaver.u8SaveIndex = 0;
	kDataSaver.u16TickCounter = 0;
	kDataSaver.u8DataProcessingIndex = 0;
	kDataSaver.eState = DataSaverState_Wait;

	if( f_mount(&SDFatFS, (TCHAR const*)SDPath, 1) != FR_OK )
	{
		AssertError(AppError_SDCardNotMounted);
	}

}

void DataSaver_Operate()
{
	if(kDataSaver.bEnabled)
	{
		switch(kDataSaver.eState)
		{
		case DataSaverState_Wait:
			if ( kDataSaver.bAveragingPeriodElapsed )
			{
				kDataSaver.eState = DataSaverState_CalculateAverage;
			}
			else if ( kDataSaver.bNewDataAvailable )
			{
				kDataSaver.eState = DataSaverState_AddToAverageSum;
			}
			break;
		case DataSaverState_AddToAverageSum:

			if( kDataSaver.u8DataProcessingIndex < dMaximumChannels )
			{
				SignalProcessing_AddSampleToAverage(kDataSaver.pkMeasurementPointer->fDataPointer[kDataSaver.u8DataProcessingIndex], kDataSaver.u8DataProcessingIndex);
				kDataSaver.u8DataProcessingIndex++;
			}
			else
			{
				kDataSaver.bNewDataAvailable = false;
				kDataSaver.u8DataProcessingIndex = 0;
				kDataSaver.eState = DataSaverState_Wait;
				kDataSaver.pkMeasurementPointer->bAddedToAverage = true;
			}
			break;
		case DataSaverState_CalculateAverage:
			SignalProcessing_CalculateAverage();
			kDataSaver.pfAveragePointer = SignalProcessing_ReadAverage();
			kDataSaver.bAveragingPeriodElapsed = false;
			kDataSaver.eState = DataSaverState_GetCurrentTime;
			break;

		case DataSaverState_GetCurrentTime:
			//todo: call RTC and convert/store data in buffer
			//todo: add function to convert RTC format into string with known pattern
			kDataSaver.eState = DataSaverState_StoreAverage;
			break;

		case DataSaverState_StoreAverage:
			if( kDataSaver.u8DataProcessingIndex < dMaximumChannels )
			{

				FrameAssembler_ConvertFloatToCharArray(
						&kDataSaver.u8SavingPage[kDataSaver.u8CurrentSavingPage][kDataSaver.u8SaveIndex],
						kDataSaver.pfAveragePointer[kDataSaver.u8DataProcessingIndex]);
				kDataSaver.u8SaveIndex += dSingleMeasurementSize;
				kDataSaver.u8DataProcessingIndex++;
			}
			else
			{
				kDataSaver.u8DataProcessingIndex = 0;
				if( (kDataSaver.u8SaveIndex - ( dSingleMeasurementSize * dMaximumChannels)) < ( dSingleMeasurementSize * dMaximumChannels) )
				{
					kDataSaver.u8SaveIndex = 0;
					kDataSaver.u8PreviousSavingPage = kDataSaver.u8CurrentSavingPage;
					kDataSaver.u8CurrentSavingPage++;
					if(kDataSaver.u8CurrentSavingPage >= dSavingPageCount)
					{
						kDataSaver.u8CurrentSavingPage = 0;
					}
					kDataSaver.eState = DataSaverState_OpenFile;
				}
				else
				{
					kDataSaver.eState = DataSaverState_Wait;
				}
			}
			break;

		case DataSaverState_OpenFile:
			kDataSaver.kCardResult = f_open(&SDFile, "Test_5.txt", FA_CREATE_ALWAYS | FA_WRITE );
			kDataSaver.eState = DataSaverState_CallSDSave;
			break;
		case DataSaverState_CallSDSave:
			//todo: add verification whether file can be safely closed
			kDataSaver.kCardResult = f_write(&SDFile, &kDataSaver.u8SavingPage[kDataSaver.u8PreviousSavingPage][0], dSavingPageSize, &kWordCount);
			kDataSaver.eState = DataSaverState_CloseFile;
			break;
		case DataSaverState_CloseFile:
			f_close(&SDFile);
			kDataSaver.eState = DataSaverState_Wait;
			break;
		default:
			break;
		}

	}
}

void DataSaver_NewDataAvailable()
{
	if( !kDataSaver.bNewDataAvailable )
	{
		kDataSaver.bNewDataAvailable = true;
		DataHandler_AccessMemoryInterchange(&kDataSaver.pkMeasurementPointer);
	}
	else
	{
		AssertError(AppError_AveragingDataOverlaped);
	}
}

void DataSaver_TickAveragingPeriod()
{
	if( kDataSaver.bEnabled )
	{
		kDataSaver.u16TickCounter++;

		if(kDataSaver.u16TickCounter >= ((uint16_t)dAveragingPeriodTicks ) )
		{
			kDataSaver.u16TickCounter = 0;
			if( !kDataSaver.bAveragingPeriodElapsed )
			{
				kDataSaver.bAveragingPeriodElapsed = true;
			}
			else
			{
				AssertError(AppError_AveragingDataLost);
			}
		}
	}
}
