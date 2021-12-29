/*
 * TemperatureSensor_MCP9803.h
 *
 *  Created on: 28 gru 2021
 *      Author: Filip
 */

#ifndef SENSORS_TEMPERATURESENSOR_MCP9803_H_
#define SENSORS_TEMPERATURESENSOR_MCP9803_H_

#include "TemperatureSensor_ArrayData.h"

#define MCP9803_AddressAmbientTemperature 	0x00
#define MCP9803_AddressConfiguration		0x01

typedef enum MCP9803_Resolution_t
{
	eMCP9803_Resolution_9bit 	= 0x00,
	eMCP9803_Resolution_10bit 	= 0x20,
	eMCP9803_Resolution_11bit 	= 0x40,
	eMCP9803_Resolution_12bit 	= 0x60
}MCP9803_Resolution_t;

void MCP9803_Read(TemperatureSensor_t *kSensor);
void MCP9803_ConfigureResolution(TemperatureSensor_t *kSensor, MCP9803_Resolution_t eBitResolution);
uint8_t MCP9803_CalculateAddress(uint8_t u8BitSettings);

float MCP9803_DecodeTemperature(TemperatureSensor_t *kSensor);

#endif /* SENSORS_TEMPERATURESENSOR_MCP9803_H_ */
