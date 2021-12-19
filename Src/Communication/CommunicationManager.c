/*
 * CommunicationManager.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#include "CommunicationManager.h"
#include "FrameAssembler.h"
#include "USBTransmitter.h"
#include "../Application/DataHandler.h"
#include "../Application/DataCommon.h"
#include "../Application/Application.h"
#include "../Drivers/BSP/BSP.h"

#define dOpeningByte	( 0x0A ) // line feed (/n) as an opening character
#define dClosingByte	( 0x0D ) // carriage return (/r) as an closing character
#define dTabASCII		( 0x09 ) // tab character (/t) to separate bytes

#define dMaxDataLenght 		( 10 )
#define dMaxTrialsCount		( 3 )

void CommManager_FlushFrame();

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
	CommunicationState_t ePreviousState;
	uint16_t u16ReadoutPointer;
	uint8_t u8Frame[dMaxDataLenght];
	uint8_t u8CurrentFrameLength;
	uint8_t u8TrialsCounter;
	bool bUSBConnected;
}CommunicationData_t;

static CommunicationData_t kCommData;

void CommManager_Initialize()
{
	kCommData.bInitialized = true;
	CommManager_FlushFrame();
}
void CommManager_Operate()
{
	bool bResult;
	float * pfPointer;
	float fValue;

	if(kCommData.bInitialized)
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
			kCommData.ePreviousState = kCommData.eState;
			kCommData.eState = Comm_Transmit;
			break;
		case Comm_AssembleFrame:

			pfPointer = kCommData.pkMemoryPointer->fDataPointer;
			fValue = pfPointer[kCommData.u16ReadoutPointer];

			FrameAssembler_ConvertFloatToCharArray(kCommData.u8Frame, fValue);
			kCommData.u8CurrentFrameLength = 10;
			kCommData.ePreviousState = kCommData.eState;
			kCommData.eState = Comm_Transmit;
			break;
		case Comm_CloseTransmission:

			kCommData.u8Frame[0] = dClosingByte;
			kCommData.u8CurrentFrameLength = 1;
			kCommData.ePreviousState = kCommData.eState;
			kCommData.eState = Comm_Transmit;
			break;
		case Comm_Transmit:

			bResult = USB_TransmitData(kCommData.u8Frame, kCommData.u8CurrentFrameLength);
			if( !bResult )
			{
				kCommData.u8TrialsCounter = 0;
				if ( kCommData.ePreviousState == Comm_AssembleFrame )
				{
					kCommData.u16ReadoutPointer++;
					kCommData.eState = Comm_AssembleFrame;
					if( kCommData.u16ReadoutPointer >= dMemoryWidth)
					{
						kCommData.eState = Comm_CloseTransmission;
						kCommData.u16ReadoutPointer = 0;
					}
				}
				else if( kCommData.ePreviousState == Comm_CloseTransmission)
				{
					kCommData.pkMemoryPointer->eMemoryState = MemoryState_DataSent;
					kCommData.eState = Comm_Idle;
				}
				else if ( kCommData.ePreviousState == Comm_OpenTransmission )
				{
					kCommData.u16ReadoutPointer = 0;
					kCommData.eState = Comm_AssembleFrame;
				}
				else
				{
					AssertError(AppError_TransmissionLogicBroken);
					kCommData.eState = Comm_Abort;
				}
			}
			else
			{
				kCommData.eState = kCommData.ePreviousState;
				kCommData.u8TrialsCounter++;
				// Additional mechanism of aborting the transmission if 3 consecutive trials are unsuccessful
				if(kCommData.u8TrialsCounter > dMaxTrialsCount)
				{
					kCommData.eState = Comm_Abort;
				}
			}
			break;
		case Comm_Receiving:

			break;
		case Comm_Abort:

			kCommData.eState = Comm_Idle;

			kCommData.pkMemoryPointer->eMemoryState = MemoryState_DataSkipped;
			kCommData.u16ReadoutPointer = 0;
			CommManager_FlushFrame();
			break;
		default:

			break;
		}
	}
}

void CommManager_SetUSBConnectionState( USBState_t eState )
{
	//todo: Add periodic change of the VSENSE pin
	if( eState == USB_Connected)
	{
		kCommData.bUSBConnected = true;
		OperateLED_C(eLED_On);
	}
	else
	{
		kCommData.bUSBConnected = false;
		kCommData.eState = Comm_Abort; // Cancel transmission - clear buffer, stop frame assembly and other;
		OperateLED_C(eLED_Off);
	}
}

void ComManager_ArmTransmission()
{
	DataHandler_AccessMemoryInterchange(&kCommData.pkMemoryPointer);

	if( kCommData.bUSBConnected)
	{
		if(kCommData.eState == Comm_Idle)
		{
			kCommData.eState = Comm_OpenTransmission;
			kCommData.u16ReadoutPointer = 0;

		}
		else
		{
			AssertError(AppError_TransmissionOverlap);
		}
	}
	else
	{
		kCommData.pkMemoryPointer->eMemoryState = MemoryState_DataSkipped;
	}

}

/* Internal functions */

void CommManager_FlushFrame()
{
	for(uint8_t u8Idx = 0; u8Idx < dMaxDataLenght; u8Idx++)
	{
		kCommData.u8Frame[u8Idx] = 0;
	}
}
