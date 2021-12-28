/*
 * TemperatureSensor_MCP9808.c
 *
 *  Created on: Sep 1, 2021
 *      Author: Filip
 */

#include "../Sensors/TemperatureSensor_MCP9808.h"

#include "TemperatureSensor_ArrayData.h"

#define MCP9808_AddresLowerNibble 0x3

void MCP9808_Read(TemperatureSensor_t *kSensor)
{
	HAL_I2C_Mem_Read_IT(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9808_AddressAmbientTemperature, 1, kSensor->u16RawMeasurement, 2);
}

uint8_t MCP9808_CalculateAddress(uint8_t u8BitSettings)
{
	return ((MCP9808_AddresLowerNibble << 4) + u8BitSettings);
}

float MCP9808_DecodeTemperature(TemperatureSensor_t *kSensor)
{
	uint16_t u16FixedPointReadingLow = 0;
	uint16_t u16FixedPointReadingHigh = 0;
	uint16_t u16FixedPointReading = 0;
	bool bNegativeSign = false;
	float fResult = 0.0;

	u16FixedPointReadingLow = ((uint16_t)(kSensor->u16RawMeasurement[0])) << 8;
	bNegativeSign = ( u16FixedPointReadingLow & 0x1000) && 0x1000;
	u16FixedPointReadingLow = u16FixedPointReadingLow & (0x0FFF); // Mask to delete threshold data and sign

	u16FixedPointReadingHigh = ((uint16_t)(kSensor->u16RawMeasurement[1]));
	u16FixedPointReading = u16FixedPointReadingLow + u16FixedPointReadingHigh;

	if (bNegativeSign)
	{
		fResult = ((float)(u16FixedPointReading) / 16) * -1;
	}
	else
	{
		fResult = ((float)(u16FixedPointReading) / 16);
	}

	return fResult;
}

