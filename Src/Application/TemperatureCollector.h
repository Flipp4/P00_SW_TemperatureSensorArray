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

#include "../../Drivers/Sensors/TemperatureSensor_ArrayData.h"

#define dSensorCount (Sensor_I2CA_DeviceCount + Sensor_I2CB_DeviceCount)

typedef enum CommunicationModule_t
{
	eModule_I2CA,
	eModule_I2CB
}CommunicationModule_t;

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
void TempCollect_CommFaultOccured(CommunicationModule_t eModule);

#endif /* APPLICATION_TEMPERATURECOLLECTOR_H_ */
