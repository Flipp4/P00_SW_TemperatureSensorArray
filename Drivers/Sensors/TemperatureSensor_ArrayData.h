/*
 * MCP9808_ArrayData.h
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#ifndef SENSORS_TEMPERATURESENSOR_ARRAYDATA_H_
#define SENSORS_TEMPERATURESENSOR_ARRAYDATA_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define Sensor_I2CA_DeviceCount 5

#define Sensor_I2CB_DeviceCount 5

typedef struct TemperatureSensor_t
{
	bool bEnabled;
	uint8_t u8Address;
	I2C_HandleTypeDef* hTranscieverHandle;
	uint8_t u16RawMeasurement[2];
	bool bNewData;
}TemperatureSensor_t;

extern TemperatureSensor_t kaSensorArrayDataA[Sensor_I2CA_DeviceCount];
extern TemperatureSensor_t kaSensorArrayDataB[Sensor_I2CB_DeviceCount];

void SensorArray_Init(I2C_HandleTypeDef *hI2CA, I2C_HandleTypeDef *hI2CB);
void SensorArray_Reset();

#endif /* SENSORS_TEMPERATURESENSOR_ARRAYDATA_H_ */
