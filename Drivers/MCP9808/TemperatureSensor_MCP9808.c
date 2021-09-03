/*
 * TemperatureSensor_MCP9808.c
 *
 *  Created on: Sep 1, 2021
 *      Author: Filip
 */

#include "TemperatureSensor_MCP9808.h"


typedef enum
{
	MCP9808_Initialized,
	MCP9808_TemperatureReadRequest,
	MCP9808_TemperatureConversion,
	MCP9808_Waiting,
	MCP9808_Error
}eCommunicationState_t;

typedef struct kMCP9808_CommData_t
{
	I2C_HandleTypeDef* hTranscieverHandle;
	uint8_t u8DeviceAddressList[8];
	uint8_t u8DeviceCount;
	bool bEnabled;
	eCommunicationState_t eState;
	bool bStateReady;
	uint16_t u16RawTemperature;
	float fConvertedTemperature;

}kMCP9808_CommData_t;

kMCP9808_CommData_t I2C1_Array;
kMCP9808_CommData_t I2C2_Array;


float MCP9808_ReadTemperature(I2C_HandleTypeDef hI2C_Transciever, uint8_t u8DeviceHWAddress);

void MCP9808_CommunicateTaskI2C1()
{

	uint16_t u16FixedPointReadingLow = 0;
	uint16_t u16FixedPointReadingHigh = 0;
	uint16_t u16FixedPointReading = 0;

	switch(I2C1_Array.eState)
	{
	case(MCP9808_Initialized):
			I2C1_Array.eState = MCP9808_TemperatureReadRequest;
			break;
	case(MCP9808_TemperatureReadRequest):
//			HAL_I2C_Master_Transmit(&hI2C_Transciever, u8DeviceAddres, &u8Buffer, 2, 1000);
			HAL_I2C_Mem_Read(I2C1_Array.hTranscieverHandle, I2C1_Array.u8DeviceAddressList[0], MCP9808_AddressAmbientTemperature, 1, &I2C1_Array.u16RawTemperature, 2, 1000);
			I2C1_Array.eState = MCP9808_TemperatureConversion;
			break;
	case(MCP9808_TemperatureConversion):
			u16FixedPointReadingLow = (I2C1_Array.u16RawTemperature & 0x003F) << 8;
			u16FixedPointReadingHigh = (I2C1_Array.u16RawTemperature & 0xFF00) >> 8;
			u16FixedPointReading = u16FixedPointReadingLow + u16FixedPointReadingHigh;
			I2C1_Array.fConvertedTemperature = (float)(u16FixedPointReading) / 16;
			I2C1_Array.eState = MCP9808_TemperatureReadRequest;
			break;
	case(MCP9808_Waiting):
			break;
	default:
	break;
	}

}


void MCP9808_InitCommunicationI2C1(I2C_HandleTypeDef *hI2C_Transciever, uint8_t *u8DeviceAddressList, uint8_t u8DeviceCount)
{
	I2C1_Array.hTranscieverHandle = hI2C_Transciever;
	for( uint8_t u8AddresIndex = 0; u8AddresIndex < u8DeviceCount; u8AddresIndex++ )
	{
		I2C1_Array.u8DeviceAddressList[u8AddresIndex] = ((MCP9808_AddresLowerNibble << 4) + u8DeviceAddressList[u8AddresIndex]);
	}
	I2C1_Array.bEnabled = true;
}


float MCP9808_ReadTemperature(I2C_HandleTypeDef hI2C_Transciever, uint8_t u8DeviceHWAddress)
{
	float fTemperature = 0.0;
	uint8_t u8DeviceAddres = (u8DeviceHWAddress | MCP9808_AddresLowerNibble);
	uint8_t u8Buffer[2];

	HAL_I2C_Master_Receive(&hI2C_Transciever, u8DeviceAddres, &u8Buffer, 2, 1000);


	return fTemperature;
}
