/*
 * DataSaver.h
 *
 *  Created on: 3 sty 2022
 *      Author: Filip
 */

#ifndef APPLICATION_DATASAVER_H_
#define APPLICATION_DATASAVER_H_

#include <stdbool.h>
#include <stdint.h>
#include  "../Signal processing/Filters.h"

#define dSingleMeasurementSize ( 10 )

#define dSavingPageCount	( 2 )
#define dFormattingCharacters ( 2 )
#define dSavingPageSize 	( (dMaximumChannels * dSingleMeasurementSize + dFormattingCharacters) * 10 )

#define dAveragingPeriodTicks	( 8 )

void DataSaver_Initialize();
void DataSaver_Operate();

void DataSaver_NewDataAvailable();
void DataSaver_TickAveragingPeriod();

#endif /* APPLICATION_DATASAVER_H_ */
