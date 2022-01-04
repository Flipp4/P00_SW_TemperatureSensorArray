/*
 * FrameAssembler.h
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#ifndef COMMUNICATION_FRAMEASSEMBLER_H_
#define COMMUNICATION_FRAMEASSEMBLER_H_

#include <stdbool.h>
#include <stdint.h>

#include "../stm32f4xx_hal.h"

void FrameAssembler_ConvertFloatToCharArray(uint8_t *pResultArray, float fNumber);
void FrameAssembler_ConvertDateTimeToCharArray(uint8_t *pResultArray, RTC_TimeTypeDef * pkTime, RTC_DateTypeDef* pkDate);
void FrameAssembler_CreateFilnameFromDate(uint8_t *pResultArray, RTC_DateTypeDef* pkDate);

#endif /* COMMUNICATION_FRAMEASSEMBLER_H_ */
