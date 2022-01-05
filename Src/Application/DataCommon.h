/*
 * DataCommon.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_DATACOMMON_H_
#define APPLICATION_DATACOMMON_H_

#include <stdbool.h>
#include <stdint.h>

#define dMemoryWidth 		( 16 )
#define dMemoryLength 		( 8 )
#define dMemoryPagesCount 	( 2 )

typedef enum MemoryState_t
{
	eMemoryState_NewData,
	eMemoryState_DataConverted,
	eMemoryState_DataSent,
	eMemoryState_DataSkipped
}MemoryState_t;

typedef struct MemoryInterchange_t
{
	float * fDataPointer;
	bool bAddedToAverage;
	MemoryState_t eMemoryState;
}MemoryInterchange_t;

#endif /* APPLICATION_DATACOMMON_H_ */
