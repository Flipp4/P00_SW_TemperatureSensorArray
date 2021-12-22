/*
 * Application.c
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */


#include "Application.h"
#include "ApplicationSystem.h"
#include "TemperatureCollector.h"
#include "DataHandler.h"
#include "EventSystem.h"

#include "../Drivers/MCP9808/TemperatureSensor_MCP9808.h"
#include "../Drivers/BSP/BSP.h"

#include "../Communication/CommunicationManager.h"
#include "../Communication/USBTransmitter.h"

/* Function prototypes */

void AsynchronousTask_1ms();
void AsynchronousTask_10ms();
void AsynchronousTask_100ms();
void AsynchronousTask_1000ms();
void AsynchronousTaskScheduler();
void AppStateChangeRequest( ApplicationState_t eNewState);
void WaitManager();
void AppEnableResetTaskTimers();
void TurnOnSynchronousEvent();

/* File-scope variables */

static volatile Application_t kApplicationBase =
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

	switch(kApplicationBase.eApplicationState)
	{
	case eApp_EntryState:
		OperateLED_A(eLED_On);
		AppStateChangeRequest(eApp_Initialization);
		break;

	case eApp_Initialization:
		AppEnableResetTaskTimers();
		TempCollect_Initialize();
		DataHandler_Initialize();
		CommManager_Initialize();
		EventSystem_Initialize();
		TurnAllSensorOn();
		TurnOnSynchronousEvent(); //todo: add actual on/off functionality to synchronous timers
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
	if(kApplicationBase.sAsyncTimers.s1000ms.bEnabledFlag)
	{
		kApplicationBase.sAsyncTimers.s1000ms.u16Counter++;
	}
	if(kApplicationBase.sAsyncTimers.s100ms.bEnabledFlag)
	{
		kApplicationBase.sAsyncTimers.s100ms.u16Counter++;
	}
	if(kApplicationBase.sAsyncTimers.s10ms.bEnabledFlag)
	{
		kApplicationBase.sAsyncTimers.s10ms.u16Counter++;
	}
	if(kApplicationBase.sAsyncTimers.s1ms.bEnabledFlag)
	{
		kApplicationBase.sAsyncTimers.s1ms.u16Counter++;
	}
	if(kApplicationBase.sAsyncTimers.s500us.bEnabledFlag)
	{
		kApplicationBase.sAsyncTimers.s500us.u16Counter++;
	}

}

/* Internal functions */

void AsynchronousTask_1ms()
{
	SetSecondDebugPinOn();
	EventSystem_HandleEvent();
	CommManager_Operate();
	SetSecondDebugPinOff();
}

void AsynchronousTask_10ms()
{
	TempCollect_Operate();
}

void AsynchronousTask_100ms()
{
	USB_CheckForUSBConnection();
	DataHandler_Operate();
}

void AsynchronousTask_1000ms()
{
	ToggleLED_B();
}

void AsynchronousTaskScheduler()
{
	if(kApplicationBase.sAsyncTimers.s1000ms.u16Counter >= dAsynchronousTaskPeriod1000ms)
	{
		AsynchronousTask_1000ms();
		kApplicationBase.sAsyncTimers.s1000ms.u16Counter = 0;
	}

	if(kApplicationBase.sAsyncTimers.s100ms.u16Counter >= dAsynchronousTaskPeriod100ms)
	{
		AsynchronousTask_100ms();
		kApplicationBase.sAsyncTimers.s100ms.u16Counter = 0;
	}

	if(kApplicationBase.sAsyncTimers.s10ms.u16Counter >= dAsynchronousTaskPeriod10ms)
	{
		AsynchronousTask_10ms();
		kApplicationBase.sAsyncTimers.s10ms.u16Counter = 0;
	}

	if(kApplicationBase.sAsyncTimers.s1ms.u16Counter >= dAsynchronousTaskPeriod1ms)
	{
		AsynchronousTask_1ms();
		kApplicationBase.sAsyncTimers.s1ms.u16Counter = 0;
	}

}

void AppStateChangeRequest( ApplicationState_t eNewState)
{
	switch(kApplicationBase.eApplicationState)
	{
	case eApp_EntryState:
		if(eNewState == eApp_Initialization)
		{
			kApplicationBase.eApplicationState = eApp_Initialization;
		}
		else
		{
			AssertError(AppError_WrongStateTransition);
		}
		break;

	case eApp_Initialization:
		if(eNewState == eApp_Perform)
		{
			kApplicationBase.eApplicationState = eApp_Perform;
		}
		else
		{
			AssertError(AppError_WrongStateTransition);
		}
		break;

	case eApp_Perform:
		if(eNewState == eApp_Initialization)
		{
			kApplicationBase.eApplicationState = eApp_Initialization;
		}
		else if(eNewState == eApp_Shutdown)
		{
			kApplicationBase.eApplicationState = eApp_Shutdown;
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
	kApplicationBase.sAsyncTimers.s1000ms.bEnabledFlag = true;
	kApplicationBase.sAsyncTimers.s100ms.bEnabledFlag = true;
	kApplicationBase.sAsyncTimers.s10ms.bEnabledFlag = true;
	kApplicationBase.sAsyncTimers.s1ms.bEnabledFlag = true;
	kApplicationBase.sAsyncTimers.s500us.bEnabledFlag = true;

	kApplicationBase.sAsyncTimers.s1000ms.u16Counter = 0;
	kApplicationBase.sAsyncTimers.s100ms.u16Counter = 0;
	kApplicationBase.sAsyncTimers.s10ms.u16Counter = 0;
	kApplicationBase.sAsyncTimers.s1ms.u16Counter = 0;
	kApplicationBase.sAsyncTimers.s500us.u16Counter = 0;
}

void AssertError( AppErrorList_t eAppError )
{
	kApplicationBase.u32ErrorReg |= (uint32_t)eAppError;
}

void TurnOnSynchronousEvent()
{

}
