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
#include "../Drivers/BSP/BSP.h"

#define dSensorResetRequiredTicks 			( 26 )
#define dSensorErrorRequiredOccurences		( 2 )
#define dSignalizationPeriod				( 30 )
#define dSignalizationDuration				( 3 )

typedef struct ErrorHandlerData_t
{
	bool bEnabled;
	uint32_t u32Register;
	uint16_t u16SensorErrorCounter;
	uint16_t u16SensorErrorLatch;
	uint16_t u16TickCounter;
	uint32_t u32SignalizationRegister;
	uint16_t u16SignalizationPeriodCounter;
	uint16_t u16SignalizationCounter;
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

	if ( (eAppError == eAppError_ArrayAError) || (eAppError == eAppError_ArrayBError) )
	{
		kErrorData.u16SensorErrorCounter++;
		kErrorData.bErrorTimeCounterEnabled = true;
	}
}

void ErrorHandler_SetSignalize(ErrorSingalizeList_t eErrorSignal)
{
	kErrorData.u32SignalizationRegister |= (uint32_t)eErrorSignal;
}

void ErrorHandler_Signalize()
{
	if ( (kErrorData.u16SignalizationPeriodCounter == 0) && (kErrorData.u32SignalizationRegister & 0x1) )
	{
		OperateLED_D(eLED_On);
	}
	else if(kErrorData.u16SignalizationPeriodCounter == dSignalizationDuration)
	{
		OperateLED_D(eLED_Off);
	}
	else if( (kErrorData.u16SignalizationPeriodCounter == (2 * dSignalizationDuration)) && (kErrorData.u32SignalizationRegister & 0x2) )
	{
		OperateLED_D(eLED_On);
	}
	else if(kErrorData.u16SignalizationPeriodCounter == (3 * dSignalizationDuration) )
	{
		OperateLED_D(eLED_Off);
	}
	else if( (kErrorData.u16SignalizationPeriodCounter == (4 * dSignalizationDuration)) && (kErrorData.u32SignalizationRegister & 0x2) )
	{
		OperateLED_D(eLED_On);
	}
	else if(kErrorData.u16SignalizationPeriodCounter == (5 * dSignalizationDuration) )
	{
		OperateLED_D(eLED_Off);
	}

	kErrorData.u16SignalizationPeriodCounter++;
	if(kErrorData.u16SignalizationPeriodCounter >= dSignalizationPeriod)
	{
		kErrorData.u16SignalizationPeriodCounter = 0;
	}
}
