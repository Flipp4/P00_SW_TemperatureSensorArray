/*
 * MCP9808_ArrayData.h
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#ifndef MCP9808_MCP9808_ARRAYDATA_H_
#define MCP9808_MCP9808_ARRAYDATA_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define MCP9808_I2CA_DeviceCount 5

#define MCP9808_I2CB_DeviceCount 5

typedef struct MCP9808_Sensor_t
{
	bool bEnabled;
	uint8_t u8Address;
	I2C_HandleTypeDef* hTranscieverHandle;
	uint8_t u16RawMeasurement[2];
	bool bNewData;
}MCP9808_Sensor_t;

extern MCP9808_Sensor_t kaSensorArrayDataA[MCP9808_I2CA_DeviceCount];
extern MCP9808_Sensor_t kaSensorArrayDataB[MCP9808_I2CB_DeviceCount];

void SensorArray_Init(I2C_HandleTypeDef *hI2CA, I2C_HandleTypeDef *hI2CB);
void SensorArray_Reset();

#endif /* MCP9808_MCP9808_ARRAYDATA_H_ */
