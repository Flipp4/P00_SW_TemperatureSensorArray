/*
 * Filters.h
 *
 *  Created on: 3 sty 2022
 *      Author: Filip
 */

#ifndef SIGNAL_PROCESSING_FILTERS_H_
#define SIGNAL_PROCESSING_FILTERS_H_

#include <stdbool.h>
#include <stdint.h>
#include "../Application/DataCommon.h"

#define dMaximumChannels ( dMemoryWidth )

void SignalProcessing_Initialize(uint8_t u8Channels);
void SignalProcessing_AddSampleToAverage(float fNewData, uint8_t u8Channel);

void SignalProcessing_CalculateAverage();
float* SignalProcessing_ReadAverage();

#endif /* SIGNAL_PROCESSING_FILTERS_H_ */
