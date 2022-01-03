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
}DataSaver_t;

static DataSaver_t kDataSaver;

void DataSaver_Initialize()
{
	kDataSaver.bEnabled = true;
	kDataSaver.u8CurrentSavingPage = 0;
	kDataSaver.u8PreviousSavingPage = 0;
	kDataSaver.u8SaveIndex = 0;
	kDataSaver.u16TickCounter = 0;
}

void DataSaver_Operate()
{

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
