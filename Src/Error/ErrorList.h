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
	eAppError_TimerError 				= 0x00001,
	eAppError_InputError				= 0x00002,
	eAppError_TaskOverlapError			= 0x00004,
	eAppError_UndefinedError			= 0x00008,

	eAppError_AppDefaultStateEntryError	= 0x00010,
	eAppError_WrongStateTransition		= 0x00020,
	eAppError_DataLost					= 0x00040,
	eAppError_WidthOverstretched		= 0x00080,

	eAppError_DataHandlerUninitialized	= 0x00100,
	eAppError_TempCollectUninitialized	= 0x00200,
	eAppError_TempCollectDefaultState	= 0x00400,
	eAppError_TempCollectRequestOverlap	= 0x00800,

	eAppError_EventOverlap				= 0x01000,
	eAppError_TransmissionOverlap		= 0x02000,
	eAppError_TransmissionLogicBroken	= 0x04000,
	eAppError_ArrayAError				= 0x08000,

	eAppError_ArrayBError				= 0x01000,
	eAppError_HALHandleAssignmentError	= 0x02000,
	eAppError_SignalProcessingError		= 0x04000,
	eAppError_AveragingDataLost			= 0x08000,

	eAppError_AveragingDataOverlaped	= 0x10000,
	eAppError_SDCardNotMounted			= 0x20000

}AppErrorList_t;

#endif /* ERROR_ERRORLIST_H_ */
