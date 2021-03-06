/*
 * ApplicationSystem.h
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */

#ifndef APPLICATION_APPLICATIONSYSTEM_H_
#define APPLICATION_APPLICATIONSYSTEM_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define dSysTickBase_us 1000

#define dAsynchronousTaskPeriod1000ms 	( 1000 * 1000 / dSysTickBase_us)
#define dAsynchronousTaskPeriod100ms 	( 100 * 1000 / dSysTickBase_us)
#define dAsynchronousTaskPeriod10ms 	( 10 * 1000 / dSysTickBase_us)
#define dAsynchronousTaskPeriod1ms 		( 1 * 1000 / dSysTickBase_us)

typedef enum ApplicationState_t
{
	eApp_EntryState,
	eApp_Initialization,
	eApp_Perform,
	eApp_Shutdown,
	eApp_StateCount

}ApplicationState_t;

typedef struct SWTimer_t
{
	bool bEnabledFlag;
	uint16_t u16Counter;

}SWTimer_t;

typedef struct AsyncTimers_t
{
	SWTimer_t s1000ms;
	SWTimer_t s100ms;
	SWTimer_t s10ms;
	SWTimer_t s1ms;
	SWTimer_t s500us;
}AsyncTimers_t;

typedef struct Application_t
{
	AsyncTimers_t sAsyncTimers;
	bool bInitializedFlag;
	ApplicationState_t eApplicationState;
	TIM_HandleTypeDef *phSynchronousEventTimer;
}Application_t;

#endif /* APPLICATION_APPLICATIONSYSTEM_H_ */
