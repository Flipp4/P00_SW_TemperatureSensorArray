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

#define Sensor_I2CA_DeviceCount 8

#define Sensor_I2CB_DeviceCount 8

typedef enum SensorType_t
{
	eSensor_MCP9808,
	eSensor_MCP9803
}SensorType_t;

typedef void ( *VoidSensorFunction)(void *kTemperatureSensor);
typedef float ( *FloatSensorFunction)(void *kTemperatureSensor);
typedef void (*VoidSensorFunction2Param)(void *kTemperatureSensor, void* eBitResolution);

typedef struct TemperatureSensor_t
{
	bool bEnabled;
	uint8_t u8Address;
	I2C_HandleTypeDef* hTranscieverHandle;
	uint8_t u16RawMeasurement[2];
	bool bNewData;
	SensorType_t eSensorType;
	FloatSensorFunction fcnDecodeTemperature;
	VoidSensorFunction fcnReadTemperature;
	VoidSensorFunction2Param fcnSendConfig;
}TemperatureSensor_t;

extern TemperatureSensor_t kaSensorArrayDataA[Sensor_I2CA_DeviceCount];
extern TemperatureSensor_t kaSensorArrayDataB[Sensor_I2CB_DeviceCount];

void SensorArray_Init();
void SensorArray_Reset();

#endif /* SENSORS_TEMPERATURESENSOR_ARRAYDATA_H_ */
