/*
 * ErrorList.h
 *
 *  Created on: 11 gru 2021
 *      Author: Filip
 */

#ifndef ERROR_ERRORLIST_H_
#define ERROR_ERRORLIST_H_

typedef enum AppErrorList_t
{
	AppError_TimerError 				= 0x0001,
	AppError_InputError					= 0x0002,
	AppError_TaskOverlapError			= 0x0004,
	AppError_UndefinedError				= 0x0008,

	AppError_AppDefaultStateEntryError	= 0x0010,
	AppError_WrongStateTransition		= 0x0020,
	AppError_DataLost					= 0x0040,
	AppError_WidthOverstretched			= 0x0080,

	AppError_DataHandlerUninitialized	= 0x0100,
	AppError_TempCollectUninitialized	= 0x0200,
	AppError_TempCollectDefaultState	= 0x0400,
	AppError_TempCollectRequestOverlap	= 0x0800,

	AppError_EventOverlap				= 0x1000,
	AppError_TransmissionOverlap		= 0x2000,
	AppError_TransmissionLogicBroken	= 0x4000,
	AppError_ArrayAError				= 0x8000,

	AppError_ArrayBError				= 0x1000

}AppErrorList_t;

#endif /* ERROR_ERRORLIST_H_ */
