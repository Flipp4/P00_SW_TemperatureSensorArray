/*
 * USBTransmitter.c
 *
 *  Created on: 15 gru 2021
 *      Author: Filip
 */

#include "USBTransmitter.h"
#include "../Application/DataHandler.h"

static uint8_t u8DataArray[ 2 * dMemoryWidth];
static uint8_t Buf[] = "Test/r/n";

void ConvertDataToBytes(float *Dataset);

bool USB_TransmitData(float *Dataset)
{
	bool bResult = false;
	uint8_t * pBuf = (uint8_t*)&u8DataArray;

	ConvertDataToBytes( Dataset );

	/*
	 * result = true means that a fault occurred
	 */

	bResult = CDC_Transmit_FS(pBuf,  2 * dMemoryWidth);
//	bResult = CDC_Transmit_FS(Buf,  6);

	return bResult;
}

void ConvertDataToBytes(float *Dataset)
{
	for(uint8_t u8Idx = 0; u8Idx < (2 * dMemoryWidth); u8Idx+=2)
	{
		u8DataArray[u8Idx] = (uint8_t)((uint16_t)Dataset[u8Idx] >> 8);
		u8DataArray[u8Idx + 1] = (uint8_t)((uint16_t)Dataset[u8Idx] && 0x00FF);
	}
}
