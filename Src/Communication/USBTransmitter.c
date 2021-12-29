/*
 * USBTransmitter.c
 *
 *  Created on: 15 gru 2021
 *      Author: Filip
 */

#include "USBTransmitter.h"

#include "../Application/ModuleInterconnect.h"
#include "../Application/DataCommon.h"
#include "../Application/HandlesAssigner.h"

#define dLowThreshold  ( 3227 )
#define dHighThreshold ( 3351 )

typedef struct USBTransmitter_t
{
	bool bInitialized;
	bool bCheckStarted;
	bool bNewMeasurement;
	bool bConnected;
	uint16_t u32MeasuredVbus;
	ADC_HandleTypeDef *phADCHandle;
}USBTransmitter_t;

static uint8_t u8DataArray[ 2 * dMemoryWidth];
static USBTransmitter_t kUSBTransmitterData;
//static uint8_t Buf[] = "Test/r/n";

void ConvertDataToBytes(float *Dataset);

void USB_InitalizeTransmitterLogic()
{
	kUSBTransmitterData.phADCHandle = HandlesAssigner_GetHandle(eHandle_ADC);
	kUSBTransmitterData.bInitialized = true;
}

bool USB_TransmitData(uint8_t *Dataset, uint8_t u8Length)
{
	bool bResult = true;

	if(kUSBTransmitterData.bInitialized)
	{
	/*
	 * result = true means that a fault occurred
	 */
	bResult = CDC_Transmit_FS(Dataset,  u8Length);
	}
	return bResult;
}

void USB_CheckForUSBConnection()
{
	if( kUSBTransmitterData.bInitialized )
	{
		if( !kUSBTransmitterData.bCheckStarted )
		{
			HAL_ADC_Start_IT(kUSBTransmitterData.phADCHandle);
			kUSBTransmitterData.bCheckStarted = true;
		}

		if( kUSBTransmitterData.bNewMeasurement )
		{
			kUSBTransmitterData.bNewMeasurement = false;
			if( (kUSBTransmitterData.u32MeasuredVbus < dLowThreshold) && kUSBTransmitterData.bConnected )
			{
				kUSBTransmitterData.bConnected = false;
				CallForUSBDisonnection();
			}
			else if ( (kUSBTransmitterData.u32MeasuredVbus > dHighThreshold) && !kUSBTransmitterData.bConnected )
			{
				kUSBTransmitterData.bConnected = true;
				CallForUSBConnection();
			}
		}
	}

}

void USB_SignalizeVBUSMeasurementReady(uint32_t u32Result)
{
	kUSBTransmitterData.bNewMeasurement = true;
	kUSBTransmitterData.u32MeasuredVbus = u32Result;
	kUSBTransmitterData.bCheckStarted = false;
}

void ConvertDataToBytes(float *Dataset)
{
	for(uint8_t u8Idx = 0; u8Idx < (2 * dMemoryWidth); u8Idx+=2)
	{
		u8DataArray[u8Idx] = (uint8_t)((uint16_t)Dataset[u8Idx] >> 8);
		u8DataArray[u8Idx + 1] = (uint8_t)((uint16_t)Dataset[u8Idx] && 0x00FF);
	}
}
