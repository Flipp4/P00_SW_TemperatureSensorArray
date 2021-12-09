/*
 * TemperatureSensor_MCP9808.c
 *
 *  Created on: Sep 1, 2021
 *      Author: Filip
 */

#include "TemperatureSensor_MCP9808.h"
#include "MCP9808_ArrayData.h"

void MCP9808_Read(MCP9808_Sensor_t *kSensor)
{
	HAL_I2C_Mem_Read_IT(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9808_AddressAmbientTemperature, 1, kSensor->u16RawMeasurement, 2);
}

float MCP9808_DecodeTemperature(MCP9808_Sensor_t *kSensor)
{
	uint16_t u16FixedPointReadingLow = 0;
	uint16_t u16FixedPointReadingHigh = 0;
	uint16_t u16FixedPointReading = 0;

	u16FixedPointReadingLow = (kSensor->u16RawMeasurement[0]) << 8;
	u16FixedPointReadingHigh = (kSensor->u16RawMeasurement[1]) >> 8;
	u16FixedPointReading = u16FixedPointReadingLow + u16FixedPointReadingHigh;

	return (float)(u16FixedPointReading) / 16;
}

