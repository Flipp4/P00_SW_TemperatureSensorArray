/*
 * TemperatureSensor_MCP9803.h
 *
 *  Created on: 28 gru 2021
 *      Author: Filip
 */

#ifndef SENSORS_TEMPERATURESENSOR_MCP9803_H_
#define SENSORS_TEMPERATURESENSOR_MCP9803_H_

#include "TemperatureSensor_ArrayData.h"

#define MCP9803_AddressAmbientTemperature 0x05

void MCP9803_Read(TemperatureSensor_t *kSensor);

float MCP9803_DecodeTemperature(TemperatureSensor_t *kSensor);

#endif /* SENSORS_TEMPERATURESENSOR_MCP9803_H_ */
