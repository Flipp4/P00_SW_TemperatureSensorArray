/*
 * MCP9808_ArrayData.c
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#include "TemperatureSensor_ArrayData.h"
#include "TemperatureSensor_MCP9803.h"
#include "TemperatureSensor_MCP9808.h"
#include "../Src/Application/HandlesAssigner.h"

/*
 *  Every MC9808 device address consists of following bytes: 0011 A0 A1 A2, where 0011 is constant and A0-A2 is hardware coded.
 */
#define MCP9808_AddresLowerNibble 0x3

TemperatureSensor_t kaSensorArrayDataA[Sensor_I2CA_DeviceCount];
TemperatureSensor_t kaSensorArrayDataB[Sensor_I2CB_DeviceCount];

const uint8_t u8DeviceAddressListA[Sensor_I2CA_DeviceCount] = {
	0x00,
	0x02,
	0x08,
	0x06,
	0x08,
	0x0A,
	0x0C,
	0x0E
};

const uint8_t u8DeviceAddressListB[Sensor_I2CB_DeviceCount] = {
	0x00,
	0x02,
	0x08,
	0x06,
	0x08,
	0x0A,
	0x0C,
	0x0E
};

const SensorType_t eSensorTypeListArrayA[Sensor_I2CA_DeviceCount] =
{
		eSensor_MCP9803,
		eSensor_MCP9803,
		eSensor_MCP9803,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808
};

const SensorType_t eSensorTypeListArrayB[Sensor_I2CB_DeviceCount] =
{
		eSensor_MCP9803,
		eSensor_MCP9803,
		eSensor_MCP9803,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808,
		eSensor_MCP9808
};

void SensorArray_Init()
{
	I2C_HandleTypeDef *hI2CA = HandlesAssigner_GetHandle(eHandle_I2C1);
	I2C_HandleTypeDef *hI2CB = HandlesAssigner_GetHandle(eHandle_I2C2);

	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CA_DeviceCount; u8Idx++)
	{
		kaSensorArrayDataA[u8Idx].eSensorType = eSensorTypeListArrayA[u8Idx];

		if(eSensorTypeListArrayA[u8Idx] == eSensor_MCP9803)
		{

			kaSensorArrayDataA[u8Idx].u8Address = MCP9803_CalculateAddress(u8DeviceAddressListA[u8Idx]);
			kaSensorArrayDataA[u8Idx].fcnDecodeTemperature = &MCP9803_DecodeTemperature;
			kaSensorArrayDataA[u8Idx].fcnReadTemperature = &MCP9803_Read;
			kaSensorArrayDataA[u8Idx].fcnSendConfig = &MCP9803_ConfigureResolution;
		}
		else if (eSensorTypeListArrayA[u8Idx] == eSensor_MCP9808)
		{
			kaSensorArrayDataA[u8Idx].u8Address = MCP9808_CalculateAddress(u8DeviceAddressListA[u8Idx]);
			kaSensorArrayDataA[u8Idx].fcnDecodeTemperature = &MCP9808_DecodeTemperature;
			kaSensorArrayDataA[u8Idx].fcnReadTemperature = &MCP9808_Read;
			//todo: manage the fact that there is no config for MCP9808
		}
		kaSensorArrayDataA[u8Idx].hTranscieverHandle = hI2CA;
		kaSensorArrayDataA[u8Idx].bEnabled = true;
	}
	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CB_DeviceCount; u8Idx++)
	{
		kaSensorArrayDataB[u8Idx].eSensorType = eSensorTypeListArrayB[u8Idx];

		if(eSensorTypeListArrayB[u8Idx] == eSensor_MCP9803)
		{
			kaSensorArrayDataB[u8Idx].u8Address = MCP9803_CalculateAddress(u8DeviceAddressListB[u8Idx]);
			kaSensorArrayDataB[u8Idx].fcnDecodeTemperature = &MCP9803_DecodeTemperature;
			kaSensorArrayDataB[u8Idx].fcnReadTemperature = &MCP9803_Read;
			kaSensorArrayDataB[u8Idx].fcnSendConfig = &MCP9803_ConfigureResolution;
		}
		else if (eSensorTypeListArrayB[u8Idx] == eSensor_MCP9808)
		{
			kaSensorArrayDataB[u8Idx].u8Address = MCP9808_CalculateAddress(u8DeviceAddressListB[u8Idx]);
			kaSensorArrayDataB[u8Idx].fcnDecodeTemperature = &MCP9808_DecodeTemperature;
			kaSensorArrayDataB[u8Idx].fcnReadTemperature = &MCP9808_Read;
			//todo: manage the fact that there is no config for MCP9808
		}
		kaSensorArrayDataB[u8Idx].hTranscieverHandle = hI2CB;
		kaSensorArrayDataB[u8Idx].bEnabled = true;
	}
}

void SensorArray_Reset()
{
	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CA_DeviceCount; u8Idx++)
	{
		kaSensorArrayDataA[u8Idx].bNewData = false;
		kaSensorArrayDataA[u8Idx].u16RawMeasurement[0] = 0;
		kaSensorArrayDataA[u8Idx].u16RawMeasurement[1] = 0;
	}
	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CB_DeviceCount; u8Idx++)
	{
		kaSensorArrayDataB[u8Idx].bNewData = false;
		kaSensorArrayDataB[u8Idx].u16RawMeasurement[0] = 0;
		kaSensorArrayDataB[u8Idx].u16RawMeasurement[1] = 0;
	}
}
