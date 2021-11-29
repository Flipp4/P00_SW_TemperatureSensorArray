/*
 * Application.c
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */


#include "Application.h"
#include "ApplicationSystem.h"
#include "..\Drivers\MCP9808\TemperatureSensor_MCP9808.h"

/* Function prototypes */

void AsynchronousTask_100ms();
void AsynchronousTask_1000ms();
void AsynchronousTaskScheduler();

/* File-scope variables */

static volatile sApplication_t sApplicationBase =
{
	.sAsyncTimers.s100ms.bEnabledFlag = false,
	.sAsyncTimers.s100ms.u16Counter = 0,
	.bInitializedFlag = false
};

/* Definitions */


/* Interfaced functions */

void ApplicationPerform()
{

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

void AsynchronousTask_100ms()
{

}

void AsynchronousTask_1000ms()
{

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
//		AsynchronousTask_10ms();
		sApplicationBase.sAsyncTimers.s10ms.u16Counter = 0;
	}

	if(sApplicationBase.sAsyncTimers.s1ms.u16Counter >= dAsynchronousTaskPeriod1ms)
	{
//		AsynchronousTask_1ms();
		sApplicationBase.sAsyncTimers.s1ms.u16Counter = 0;
	}

}
