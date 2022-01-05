/*
 * ErrorHandler.c
 *
 *  Created on: 5 sty 2022
 *      Author: Filip
 */

#include <stdbool.h>
#include <stdint.h>
#include "ErrorHandler.h"
#include "../Application/ModuleInterconnect.h"

#define dSensorResetRequiredTicks 			( 26 )
#define dSensorErrorRequiredOccurences		( 2 )

typedef struct ErrorHandlerData_t
{
	bool bEnabled;
	uint32_t u32Register;
	uint16_t u16SensorErrorCounter;
	uint16_t u16SensorErrorLatch;
	uint16_t u16TickCounter;
	bool bErrorTimeCounterEnabled;
}ErrorHandlerData_t;

static ErrorHandlerData_t kErrorData;

void ErrorHandler_Initalize()
{
	kErrorData.bEnabled = true;
}

void ErrorHandler_Tick()
{
	if( kErrorData.bErrorTimeCounterEnabled)
	{
		kErrorData.u16TickCounter++;
	}
}

void ErrorHandler_Handle()
{
	if( kErrorData.u16TickCounter >= dSensorResetRequiredTicks )
	{
		if( kErrorData.u16SensorErrorCounter >= dSensorErrorRequiredOccurences )
		{
			CallForSensorReset();
		}
		kErrorData.bErrorTimeCounterEnabled = false;
		kErrorData.u16TickCounter = 0;
		kErrorData.u16SensorErrorCounter = 0;
	}
}

void AssertError( AppErrorList_t eAppError )
{
	kErrorData.u32Register |= (uint32_t)eAppError;

	if ( (eAppError == AppError_ArrayAError) || (eAppError == AppError_ArrayBError) )
	{
		kErrorData.u16SensorErrorCounter++;
		kErrorData.bErrorTimeCounterEnabled = true;
	}
}
