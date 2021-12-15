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

#define dMemoryWidth 		( 16 )
#define dMemoryLength 		( 8 )
#define dMemoryPagesCount 	( 2 )

void DataHandler_Initialize();
void DataHandler_Reset();
void DataHandler_OpenNewMeasurement( uint32_t u32TimeStamp );

#if dStoreReultsAsFloat
void DataHandler_StoreMeasurement( float fNewMeasurement );
#else
void DataHandler_StoreMeasurement( int16_t i16NewMeasurement );
#endif

void DataHandler_Operate();

#endif /* APPLICATION_DATAHANDLER_H_ */
