/*
 * Application.c
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */


#include "Application.h"
#include "ApplicationSystem.h"
#include "..\Drivers\MCP9808\TemperatureSensor_MCP9808.h"
#include "../Drivers/BSP/BSP.h"
#include "TemperatureCollector.h"
#include "DataHandler.h"

/* Function prototypes */

void AsynchronousTask_10ms();
void AsynchronousTask_100ms();
void AsynchronousTask_1000ms();
void AsynchronousTaskScheduler();
void AppStateChangeRequest( ApplicationState_t eNewState);
void WaitManager();
void AppEnableResetTaskTimers();
void TurnOnSynchronousEvent();

/* File-scope variables */

static volatile sApplication_t sApplicationBase =
{
	.sAsyncTimers.s100ms.bEnabledFlag = false,
	.sAsyncTimers.s100ms.u16Counter = 0,
	.bInitializedFlag = false,
	.eApplicationState = eApp_EntryState
};

/* Definitions */


/* Interfaced functions */

void ApplicationPerform()
{

	switch(sApplicationBase.eApplicationState)
	{
	case eApp_EntryState:
		OperateLED_A(eLED_On);
		AppStateChangeRequest(eApp_Initialization);
		break;

	case eApp_Initialization:
		AppEnableResetTaskTimers();
		TempCollect_Initialize();
		DataHandler_Initialize();
		TurnAllSensorOn();
		TurnOnSynchronousEvent();
		AppStateChangeRequest(eApp_Perform);
		break;

	case eApp_Perform:
		AsynchronousTaskScheduler();
		break;

	case eApp_Shutdown:
		break;

	default:
		AssertError(AppError_AppDefaultStateEntryError);
		break;
	}

}

void AsynchronousTaskTimerUpdate()
{
	if(sApplicationBase.sAsyncTimers.s1000ms.bEnabledFlag)
	{
		sApplicationBase.sAsyncTimers.s1000ms.u16Counter++;
	}
	if(sApplicationBase.sAsyncTimers.s100ms.bEnabledFlag)
	{
		sApplicationBase.sAsyncTimers.s100ms.u16Counter++;
	}
	if(sApplicationBase.sAsyncTimers.s10ms.bEnabledFlag)
	{
		sApplicationBase.sAsyncTimers.s10ms.u16Counter++;
	}
	if(sApplicationBase.sAsyncTimers.s1ms.bEnabledFlag)
	{
		sApplicationBase.sAsyncTimers.s1ms.u16Counter++;
	}
	if(sApplicationBase.sAsyncTimers.s500us.bEnabledFlag)
	{
		sApplicationBase.sAsyncTimers.s500us.u16Counter++;
	}

}

/* Internal functions */
void AsynchronousTask_10ms()
{
	TempCollect_Operate();
}

void AsynchronousTask_100ms()
{

}

void AsynchronousTask_1000ms()
{
	ToggleLED_B();
	DataHandler_Operate();
}

void AsynchronousTaskScheduler()
{
	if(sApplicationBase.sAsyncTimers.s1000ms.u16Counter >= dAsynchronousTaskPeriod1000ms)
	{
		AsynchronousTask_1000ms();
		sApplicationBase.sAsyncTimers.s1000ms.u16Counter = 0;
	}

	if(sApplicationBase.sAsyncTimers.s100ms.u16Counter >= dAsynchronousTaskPeriod100ms)
	{
		AsynchronousTask_100ms();
		sApplicationBase.sAsyncTimers.s100ms.u16Counter = 0;
	}

	if(sApplicationBase.sAsyncTimers.s10ms.u16Counter >= dAsynchronousTaskPeriod10ms)
	{
		AsynchronousTask_10ms();
		sApplicationBase.sAsyncTimers.s10ms.u16Counter = 0;
	}

	if(sApplicationBase.sAsyncTimers.s1ms.u16Counter >= dAsynchronousTaskPeriod1ms)
	{
//		AsynchronousTask_1ms();
		sApplicationBase.sAsyncTimers.s1ms.u16Counter = 0;
	}

}

void AppStateChangeRequest( ApplicationState_t eNewState)
{
	switch(sApplicationBase.eApplicationState)
	{
	case eApp_EntryState:
		if(eNewState == eApp_Initialization)
		{
			sApplicationBase.eApplicationState = eApp_Initialization;
		}
		else
		{
			AssertError(AppError_WrongStateTransition);
		}
		break;

	case eApp_Initialization:
		if(eNewState == eApp_Perform)
		{
			sApplicationBase.eApplicationState = eApp_Perform;
		}
		else
		{
			AssertError(AppError_WrongStateTransition);
		}
		break;

	case eApp_Perform:
		if(eNewState == eApp_Initialization)
		{
			sApplicationBase.eApplicationState = eApp_Initialization;
		}
		else if(eNewState == eApp_Shutdown)
		{
			sApplicationBase.eApplicationState = eApp_Shutdown;
		}
		else
		{
			AssertError(AppError_WrongStateTransition);
		}
		break;

	case eApp_Shutdown:
		AssertError(AppError_WrongStateTransition);
		break;

	default:
		AssertError(AppError_WrongStateTransition);
		break;
	}

}

void AppEnableResetTaskTimers()
{
	sApplicationBase.sAsyncTimers.s1000ms.bEnabledFlag = true;
	sApplicationBase.sAsyncTimers.s100ms.bEnabledFlag = true;
	sApplicationBase.sAsyncTimers.s10ms.bEnabledFlag = true;
	sApplicationBase.sAsyncTimers.s1ms.bEnabledFlag = true;
	sApplicationBase.sAsyncTimers.s500us.bEnabledFlag = true;

	sApplicationBase.sAsyncTimers.s1000ms.u16Counter = 0;
	sApplicationBase.sAsyncTimers.s100ms.u16Counter = 0;
	sApplicationBase.sAsyncTimers.s10ms.u16Counter = 0;
	sApplicationBase.sAsyncTimers.s1ms.u16Counter = 0;
	sApplicationBase.sAsyncTimers.s500us.u16Counter = 0;
}

void AssertError( AppErrorList_t eAppError )
{
	sApplicationBase.u32ErrorReg |= (uint32_t)eAppError;
}

void TurnOnSynchronousEvent()
{

}
