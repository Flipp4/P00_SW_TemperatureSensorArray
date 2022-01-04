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

#include "../Communication/DataFormat.h"

#include  "../Signal processing/Filters.h"

#define dSavingPageCount	( 2 )
#define dFormattingCharacters ( 2 )
#define dSingleEntryLength ( dMaximumChannels * dMaxDataLenght )
#define dSavingPageSize 	( ( dSingleEntryLength + dFormattingCharacters + dTimestampSize ) * 10 )

#define dAveragingPeriodTicks	( 10 )

void DataSaver_Initialize();
void DataSaver_Operate();

void DataSaver_NewDataAvailable();
void DataSaver_TickAveragingPeriod();

#endif /* APPLICATION_DATASAVER_H_ */
