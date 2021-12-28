/*
 * TemperatureSensor_MCP9808.h
 *
 *  Created on: Sep 1, 2021
 *      Author: Filip
 */

#ifndef SENSORS_TEMPERATURESENSOR_MCP9808_H_
#define SENSORS_TEMPERATURESENSOR_MCP9808_H_

#include "TemperatureSensor_ArrayData.h"

#define MCP9808_AddressAmbientTemperature 0x05

void MCP9808_Read(TemperatureSensor_t *kSensor);

float MCP9808_DecodeTemperature(TemperatureSensor_t *kSensor);

#endif /* SENSORS_TEMPERATURESENSOR_MCP9808_H_ */
