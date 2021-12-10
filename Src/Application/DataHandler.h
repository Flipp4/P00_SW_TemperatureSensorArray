/*
 * DataHandler.h
 *
 *  Created on: Dec 9, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_DATAHANDLER_H_
#define APPLICATION_DATAHANDLER_H_

#include <stdbool.h>
#include <stdint.h>

void DataHandler_OpenNewMeasurement( uint32_t u32TimeStamp );
void DataHandler_StoreMeasurement( float fNewMeasurement );

#endif /* APPLICATION_DATAHANDLER_H_ */
