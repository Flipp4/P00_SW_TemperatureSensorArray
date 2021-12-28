/*
 * TemperatureSensor_MCP9803.c
 *
 *  Created on: 28 gru 2021
 *      Author: Filip
 */

#include "../Sensors/TemperatureSensor_MCP9808.h"

#include "TemperatureSensor_ArrayData.h"

void MCP9803_Read(TemperatureSensor_t *kSensor)
{
	HAL_I2C_Mem_Read_IT(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9803_AddressAmbientTemperature, 1, kSensor->u16RawMeasurement, 2);
}


float MCP9803_DecodeTemperature(TemperatureSensor_t *kSensor)
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
