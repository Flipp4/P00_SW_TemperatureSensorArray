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

void MCP9808_CommunicateTaskI2C1();
void MCP9808_InitCommunicationI2C1(I2C_HandleTypeDef *hI2C_Transciever, uint8_t *u8DeviceAddressList, uint8_t u8DeviceCount);

#endif /* MCP9808_TEMPERATURESENSOR_MCP9808_H_ */
