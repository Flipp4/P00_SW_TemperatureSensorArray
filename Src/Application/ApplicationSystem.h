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

typedef struct ErrorRegister_t
{
	bool bTimerError;
	bool bInputError;
	bool bTaskOverlapError;
	bool bUndefinedError;
	bool bAppDefaultStateEntryError;
	bool bWrongStateTransitionError;
}ErrorRegister_t;

typedef struct sApplication_t
{
	AsyncTimers_t sAsyncTimers;
	ErrorRegister_t sErrorReg;
	bool bInitializedFlag;
	ApplicationState_t eApplicationState;

}sApplication_t;


#endif /* APPLICATION_APPLICATIONSYSTEM_H_ */
