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

void FrameAssembler_ConvertFloatToCharArray(uint8_t *pResultArray, float fNumber);

#endif /* COMMUNICATION_FRAMEASSEMBLER_H_ */
