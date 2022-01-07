/*
 * Application.c
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */


#include "Application.h"

#include "../../Drivers/Sensors/TemperatureSensor_MCP9808.h"
#include "ApplicationSystem.h"
#include "TemperatureCollector.h"
#include "DataHandler.h"
#include "EventSystem.h"
#include "HandlesAssigner.h"
#include "DataSaver.h"

#include "../Error/Supervisor.h"

#include "../Drivers/BSP/BSP.h"
#include "../Drivers/BSP/PWM_Generator.h"
#include "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

#include "../Communication/CommunicationManager.h"
#include "../Communication/USBTransmitter.h"

#include "../Signal processing/Filters.h"

#include "../Middlewares/Third_Party/FatFs/src/ff.h"

#include "../Inc/fatfs.h"

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
		OperateLED_B(eLED_On);
		OperateLED_C(eLED_On);
		OperateLED_D(eLED_On);

		kApplicationBase.phSynchronousEventTimer = HandlesAssigner_GetHandle(eHandle_TIM2);
		AppStateChangeRequest(eApp_Initialization);
		break;

	case eApp_Initialization:
		ErrorHandler_Initalize();
		Supervisor_Initialize();
		SensorArray_Init();
		USB_InitalizeTransmitterLogic();
		AppEnableResetTaskTimers();
		TempCollect_Initialize();
		DataHandler_Initialize();
		CommManager_Initialize();
		EventSystem_Initialize();
		SignalProcessing_Initialize((uint8_t)dMemoryWidth);
		DataSaver_Initialize();
		PWMGenerator_Initialize();
//		PWMGenerator_TurnPWMTimerOn();
		TurnOnSynchronousEvent();

		OperateLED_A(eLED_Off);
		OperateLED_B(eLED_Off);
		OperateLED_C(eLED_Off);
		OperateLED_D(eLED_Off);

		AppStateChangeRequest(eApp_Perform);
		break;

	case eApp_Perform:
		AsynchronousTaskScheduler();
		break;

	case eApp_Shutdown:
		break;

	default:
		AssertError(eAppError_AppDefaultStateEntryError);
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

	/* Measured time:
	 * 10 us with no frame assembly,
	 * 70 us with frame assembly
	 *
	 * two functions (22.12.2201): EventSystem and CommManager
	 */
	EventSystem_HandleEvent();
	CommManager_Operate();
	DataSaver_Operate();
	ErrorHandler_Handle();
}

void AsynchronousTask_10ms()
{
	/* Measured time:
	 * 5-10 us with no communication
	 * 1-9 us with communication
	 *
	 * one function (22.12.2201): TempCollect
	 */
	TempCollect_Operate();
	ErrorHandler_Tick();
}

void AsynchronousTask_100ms()
{
	/* Measured time:
	 * 8-11 us with no communication
	 * same with communication
	 *
	 * two functions (22.12.2201): USB_Check and DataHandler
	 */
	USB_CheckForUSBConnection();
	DataHandler_Operate();
	ErrorHandler_Signalize();
}

void AsynchronousTask_1000ms()
{
	/* Measured execution period:
	 * 999 ms without communication
	 * same with communication
	 *
	 * Measured 22.12.2021
	 */
	ToggleLED_B();
	Supervisor_Verify();
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
			AssertError(eAppError_WrongStateTransition);
		}
		break;

	case eApp_Initialization:
		if(eNewState == eApp_Perform)
		{
			kApplicationBase.eApplicationState = eApp_Perform;
		}
		else
		{
			AssertError(eAppError_WrongStateTransition);
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
			AssertError(eAppError_WrongStateTransition);
		}
		break;

	case eApp_Shutdown:
		AssertError(eAppError_WrongStateTransition);
		break;

	default:
		AssertError(eAppError_WrongStateTransition);
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

void TurnOnSynchronousEvent()
{
	 HAL_TIM_Base_Start_IT(kApplicationBase.phSynchronousEventTimer);
}
