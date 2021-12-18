/*
 * CommunicationManager.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#include "CommunicationManager.h"
#include "../Application/DataHandler.h"
#include "../Application/DataCommon.h"
#include "../Application/Application.h"

typedef enum CommunicationState_t
{
	Comm_Initialized,
	Comm_Idle,
	Comm_AssemblingFrame,
	Comm_Transmitting,
	Comm_Receiving,
	Comm_Abort
}CommunicationState_t;

typedef struct CommunicationData_t
{
	bool bInitialized;
	MemoryInterchange_t *pkMemoryPointer;
	CommunicationState_t eState;
	uint16_t u16ReadoutPointer;
	bool bUSBConnected;
}CommunicationData_t;

static CommunicationData_t kCommData;

void CommManager_Initialize()
{
	kCommData.bInitialized = true;
}
void CommManager_Operate()
{
	switch (kCommData.eState)
	{
	case Comm_Initialized:
		kCommData.eState = Comm_Idle;
		break;
	case Comm_Idle:
		break;
	case Comm_AssemblingFrame:
		break;
	case Comm_Transmitting:
		break;
	case Comm_Receiving:
		break;
	case Comm_Abort:
		break;
	default:
		break;
	}
}

void CommManager_SetUSBConnectionState( USBState_t eState )
{
	//todo: Add periodic change of the VSENSE pin
	if( eState == USB_Connected)
	{
		kCommData.bUSBConnected = true;
	}
	else
	{
		kCommData.bUSBConnected = false;
		kCommData.eState = Comm_Abort; // Cancel transmission - clear buffer, stop frame assembly and other;
	}
}

void ComManager_ArmTransmission()
{
	if( kCommData.bUSBConnected)
	{
		if(kCommData.eState == Comm_Idle)
		{
			kCommData.eState = Comm_AssemblingFrame;
			kCommData.u16ReadoutPointer = 0;
			DataHandler_AccessMemoryInterchange(kCommData.pkMemoryPointer);
		}
		else
		{
			AssertError(AppError_TransmissionOverlap);
		}
	}
}
