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

#define MCP9808_I2CA_DeviceCount 8
#define MCP9808_I2CB_DeviceCount 8

typedef struct MCP9808_Sensor_t
{
	bool bEnabled;
	uint8_t u8Address;
	I2C_HandleTypeDef* hTranscieverHandle;
	uint16_t u16RawMeasurement;
	bool bNewData;
}MCP9808_Sensor_t;

extern volatile MCP9808_Sensor_t kaSensorArrayDataA[MCP9808_I2CA_DeviceCount];
extern volatile MCP9808_Sensor_t kaSensorArrayDataB[MCP9808_I2CB_DeviceCount];

void SensorArray_Init(I2C_HandleTypeDef *hI2CA, I2C_HandleTypeDef *hI2CB);
void SensorArray_Reset();

#endif /* MCP9808_MCP9808_ARRAYDATA_H_ */
