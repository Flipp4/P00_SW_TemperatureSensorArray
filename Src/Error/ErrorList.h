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
	AppError_TimerError 				= 0x00001,
	AppError_InputError					= 0x00002,
	AppError_TaskOverlapError			= 0x00004,
	AppError_UndefinedError				= 0x00008,

	AppError_AppDefaultStateEntryError	= 0x00010,
	AppError_WrongStateTransition		= 0x00020,
	AppError_DataLost					= 0x00040,
	AppError_WidthOverstretched			= 0x00080,

	AppError_DataHandlerUninitialized	= 0x00100,
	AppError_TempCollectUninitialized	= 0x00200,
	AppError_TempCollectDefaultState	= 0x00400,
	AppError_TempCollectRequestOverlap	= 0x00800,

	AppError_EventOverlap				= 0x01000,
	AppError_TransmissionOverlap		= 0x02000,
	AppError_TransmissionLogicBroken	= 0x04000,
	AppError_ArrayAError				= 0x08000,

	AppError_ArrayBError				= 0x01000,
	AppError_HALHandleAssignmentError	= 0x02000,
	AppError_SignalProcessingError		= 0x04000,
	AppError_AveragingDataLost			= 0x08000,

	AppError_AveragingDataOverlaped		= 0x10000,
	AppError_SDCardNotMounted			= 0x20000

}AppErrorList_t;

#endif /* ERROR_ERRORLIST_H_ */
