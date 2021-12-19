/*
 * FrameAssembler.c
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#include "FrameAssembler.h"
#include <stdio.h>

void FrameAssembler_ConvertFloatToCharArray(uint8_t *pResultArray, float fNumber)
{
	sprintf((char*)pResultArray,"%f+10.4\t",fNumber);
}
