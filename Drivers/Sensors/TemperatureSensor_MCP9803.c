/*
 * TemperatureSensor_MCP9803.c
 *
 *  Created on: 28 gru 2021
 *      Author: Filip
 */

#include "../Sensors/TemperatureSensor_MCP9803.h"

#include "TemperatureSensor_ArrayData.h"

#define MCP9803_AddresLowerNibble 0x9

void MCP9803_Read(TemperatureSensor_t *kSensor)
{
	HAL_I2C_Mem_Read_IT(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9803_AddressAmbientTemperature, 1, kSensor->u16RawMeasurement, 2);
}

uint8_t MCP9803_CalculateAddress(uint8_t u8BitSettings)
{
	return ((MCP9803_AddresLowerNibble << 4) + u8BitSettings);
}

float MCP9803_DecodeTemperature(TemperatureSensor_t *kSensor)
{
	uint16_t u16FixedPointReadingLow = 0;
	uint16_t u16FixedPointReadingHigh = 0;
	bool bNegativeSign = false;
	float fResult = 0.0;


	u16FixedPointReadingLow = ((uint16_t)(kSensor->u16RawMeasurement[0]));
	bNegativeSign = ( u16FixedPointReadingLow & 0x80) && 0x80;
	u16FixedPointReadingLow = u16FixedPointReadingLow & (0x007F); // Mask to delete threshold data and sign

	u16FixedPointReadingHigh = ((uint16_t)(kSensor->u16RawMeasurement[1])) >> 4;

	if (bNegativeSign)
	{
		fResult = (((float)u16FixedPointReadingLow) + (((float)u16FixedPointReadingHigh) * 0.0625)) * -1;
	}
	else
	{
		fResult = ((float)u16FixedPointReadingLow) + (((float)u16FixedPointReadingHigh) * 0.0625);
	}

	return fResult;
}
