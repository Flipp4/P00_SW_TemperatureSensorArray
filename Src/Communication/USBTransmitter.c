/*
 * USBTransmitter.c
 *
 *  Created on: 15 gru 2021
 *      Author: Filip
 */

#include "USBTransmitter.h"
#include "../Application/DataHandler.h"

static uint8_t u8DataArray[ 2 * dMemoryWidth];

void ConvertDataToBytes(int16_t *Dataset);

#if dStoreReultsAsFloat
bool USB_TransmitData(float *Dataset)
#else
bool USB_TransmitData(int16_t *Dataset)
#endif
{
	bool bResult = false;
	uint8_t * pBuf = &u8DataArray;

	ConvertDataToBytes( Dataset );

	/*
	 * result = true means that a fault occurred
	 */

	bResult = CDC_Transmit_FS(pBuf,  2 * dMemoryWidth);

	return bResult;
}

void ConvertDataToBytes(int16_t *Dataset)
{
	for(uint8_t u8Idx = 0; u8Idx < (2 * dMemoryWidth); u8Idx+=2)
	{
		u8DataArray[u8Idx] = (uint8_t)((uint16_t)Dataset[u8Idx] >> 8);
		u8DataArray[u8Idx + 1] = (uint8_t)((uint16_t)Dataset[u8Idx] && 0x00FF);
	}
}
