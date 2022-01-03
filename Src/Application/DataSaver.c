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
	float* pfMeasurementPointer;
	float* pfAveragePointer;
	uint16_t u16TickCounter;
	DataSaverState_t eState;
}DataSaver_t;

static DataSaver_t kDataSaver;

void DataSaver_Initialize()
{
	kDataSaver.bEnabled = true;
	kDataSaver.u8CurrentSavingPage = 0;
	kDataSaver.u8PreviousSavingPage = 0;
	kDataSaver.u8SaveIndex = 0;
	kDataSaver.u16TickCounter = 0;
	kDataSaver.eState = DataSaverState_Wait;
}

void DataSaver_Operate()
{
	if(kDataSaver.bEnabled)
	{
		switch(kDataSaver.eState)
		{

		}

	}
}

void DataSaver_NewDataAvailable()
{
	if( !kDataSaver.bNewDataAvailable )
	{
		kDataSaver.bNewDataAvailable = true;
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
