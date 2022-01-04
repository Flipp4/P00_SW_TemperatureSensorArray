/*
 * FrameAssembler.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#include <stdio.h>
#include "FrameAssembler.h"
#include "DataFormat.h"

void FrameAssembler_ConvertFloatToCharArray(uint8_t *pResultArray, float fNumber)
{
//	sprintf((char*)pResultArray,"%+9.4f\t",fNumber);
	sprintf((char*)pResultArray, "%+" dPrintfSize "." dFractionSize "f\t", fNumber);
}

void FrameAssembler_ConvertDateTimeToCharArray(uint8_t *pResultArray, RTC_TimeTypeDef * pkTime, RTC_DateTypeDef* pkDate)
{
	uint8_t u8SecondFraction = (uint8_t)( ((pkTime->SecondFraction - pkTime->SubSeconds) * 10 )/(1 + pkTime->SecondFraction));

	sprintf((char*)pResultArray, "%2d.%2d.%2d ", pkDate->Date, pkDate->Month, pkDate->Year);
	sprintf(((char*)pResultArray+dDateSize), "%2d:%2d:%2d.%1d\t", pkTime->Hours, pkTime->Minutes, pkTime->Seconds, u8SecondFraction);
}

void FrameAssembler_CreateFilnameFromDate(uint8_t *pResultArray, RTC_DateTypeDef* pkDate)
{
	sprintf((char*)pResultArray, "%02d_%02d_%02d.txt", pkDate->Date, pkDate->Month, pkDate->Year);
}
