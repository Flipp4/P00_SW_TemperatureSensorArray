/*
 * TemperatureSensor_MCP9803.c
 *
 *  Created on: 28 gru 2021
 *      Author: Filip
 */

#include "../Sensors/TemperatureSensor_MCP9803.h"

#include "TemperatureSensor_ArrayData.h"

#define MCP9803_AddresLowerNibble 		( 0x9 )
/*
 * Following byteset is configured as a mask for MCP9803 config register: all values are power-up defaults
 * despite of the bits 5-6 - responsible for resolution
 */
#define MCP9803_ResolutionConfigMask	( 0x60 )
/* Since initialization is made in blocking mode there is a necessity for a timeout */
#define MCP9803_InitizalizationTimeout	( 50 )

void MCP9803_Read(TemperatureSensor_t *kSensor)
{
	HAL_I2C_Mem_Read_IT(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9803_AddressAmbientTemperature, 1, kSensor->u16RawMeasurement, 2);
}

void MCP9803_ConfigureResolution(TemperatureSensor_t *kSensor, MCP9803_Resolution_t eBitResolution)
{
	static uint8_t u8Data;
	u8Data = ((uint8_t)eBitResolution) & MCP9803_ResolutionConfigMask;

	HAL_StatusTypeDef Result = HAL_I2C_Mem_Write(kSensor->hTranscieverHandle, kSensor->u8Address, MCP9803_AddressConfiguration, 1, &u8Data, 1, MCP9803_InitizalizationTimeout);

	if(Result == HAL_OK)
	{
		u8Data = 0;
	}
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
