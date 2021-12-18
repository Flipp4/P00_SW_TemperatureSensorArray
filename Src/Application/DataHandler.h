/*
 * DataHandler.h
 *
 *  Created on: Dec 9, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_DATAHANDLER_H_
#define APPLICATION_DATAHANDLER_H_

#include "Application.h"
#include <stdbool.h>
#include <stdint.h>

void DataHandler_Initialize();
void DataHandler_Reset();
void DataHandler_OpenNewMeasurement( uint32_t u32TimeStamp );
void DataHandler_StoreMeasurement( float fNewMeasurement );
void DataHandler_Operate();

#endif /* APPLICATION_DATAHANDLER_H_ */
