/*
 * TemperatureSensor_MCP9808.h
 *
 *  Created on: Sep 1, 2021
 *      Author: Filip
 */

#ifndef MCP9808_TEMPERATURESENSOR_MCP9808_H_
#define MCP9808_TEMPERATURESENSOR_MCP9808_H_

#include "MCP9808_ArrayData.h"

#define MCP9808_AddressAmbientTemperature 0x05

void MCP9808_Read(MCP9808_Sensor_t *kSensor);

#if dStoreReultsAsFloat

float MCP9808_DecodeTemperature(MCP9808_Sensor_t *kSensor);

#else

int16_t MCP9808_DecodeTemperature(MCP9808_Sensor_t *kSensor);

#endif

#endif /* MCP9808_TEMPERATURESENSOR_MCP9808_H_ */
