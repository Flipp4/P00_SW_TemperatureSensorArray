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

#define dOpeningByte	( 0x0A ) // line feed (/n) as an opening character
#define dClosingByte	( 0x0D ) // carriage return (/r) as an closing character

#define dMaxDataLenght 		( 10 )

typedef enum CommunicationState_t
{
	Comm_Initialized,
	Comm_Idle,
	Comm_OpenTransmission,
	Comm_AssembleFrame,
	Comm_CloseTransmission,
	Comm_Transmit,
	Comm_Receiving,
	Comm_Abort
}CommunicationState_t;

typedef struct CommunicationData_t
{
	bool bInitialized;
	MemoryInterchange_t *pkMemoryPointer;
	CommunicationState_t eState;
	uint16_t u16ReadoutPointer;
	uint8_t u8Frame[dMaxDataLenght];
	uint8_t u8CurrentFrameLength;
	bool bUSBConnected;
	bool bLastByte;
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
		//Wait for new Arm_Transmission call
		break;
	case Comm_OpenTransmission:
		kCommData.u8Frame[0] = dOpeningByte;
		kCommData.u8CurrentFrameLength = 1;
		kCommData.eState = Comm_Transmit;
		break;
	case Comm_AssembleFrame:
		break;
	case Comm_CloseTransmission:
		kCommData.u8Frame[0] = dClosingByte;
		kCommData.u8CurrentFrameLength = 1;
		kCommData.eState = Comm_Transmit;
		kCommData.bLastByte = true;
		break;
	case Comm_Transmit:
		if( kCommData.u16ReadoutPointer >= dMemoryWidth)
		{
			kCommData.eState = Comm_CloseTransmission;
		}
		else if (kCommData.bLastByte)
		{
			kCommData.bLastByte = false;
			kCommData.pkMemoryPointer->eMemoryState = MemoryState_DataSent;
			kCommData.eState = Comm_Idle;
		}
		else
		{
			kCommData.eState = Comm_AssembleFrame;
		}
		break;
	case Comm_Receiving:
		break;
	case Comm_Abort:
		kCommData.eState = Comm_Idle;

		kCommData.pkMemoryPointer->eMemoryState = MemoryState_DataSkipped;
		kCommData.u16ReadoutPointer = 0;
		kCommData.u8Frame[0] = 0; //todo: replace with Frame_Flush with for
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
			kCommData.eState = Comm_AssembleFrame;
			kCommData.u16ReadoutPointer = 0;
			DataHandler_AccessMemoryInterchange(kCommData.pkMemoryPointer);
		}
		else
		{
			AssertError(AppError_TransmissionOverlap);
		}
	}
}
