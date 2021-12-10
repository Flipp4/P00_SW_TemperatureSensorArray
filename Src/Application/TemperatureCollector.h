/*
 * TemperatureCollector.h
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#ifndef APPLICATION_TEMPERATURECOLLECTOR_H_
#define APPLICATION_TEMPERATURECOLLECTOR_H_


#include <stdbool.h>
#include <stdint.h>
#include "../Drivers/MCP9808/MCP9808_ArrayData.h"

#define dSensorCount (MCP9808_I2CA_DeviceCount + MCP9808_I2CB_DeviceCount)

typedef struct TemperatureData_t
{
	float faTemperatureMeasurements[dSensorCount];
	uint32_t u32TemperatureCRC;
	bool bNewReadingFlag;
	uint32_t u32TimeStamp;
}TemperatureData_t;

void TempCollect_Operate();
void TempCollect_Initialize();
void TempCollect_RetrieveResult(TemperatureData_t *sTemperatureData);

/* Functions used by interrupts */
void TempCollect_ScheduleMeasurement();
void TempCollect_I2CA_Done();
void TempCollect_I2CB_Done();

#endif /* APPLICATION_TEMPERATURECOLLECTOR_H_ */
