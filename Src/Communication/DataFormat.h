/*
 * DataFormat.h
 *
 *  Created on: 4 sty 2022
 *      Author: Filip
 */

#ifndef COMMUNICATION_DATAFORMAT_H_
#define COMMUNICATION_DATAFORMAT_H_

#include <stdint.h>

#define dFractionSize 	 "4"

#define dDelimiterCharacter 	 "\t"
/*
 * Maximum single measurement string length including tab character, sign, decimal, dot and fractional part
 */

#define dMaxDataLenght 		 ( 10 )

/*
 * dPrintfSize shall be a number (in char format) that is equal to dMaxDataLength - size of dDelimiterCharcter - null character at the end
 */
#define dPrintfSize   "8"

#define dDateSize 			( 9 )
#define dTimeSize 			( 11 )
#define dTimestampSize 		( dDateSize + dTimeSize )

#define dFilenameLength 	(12)

#define dErrorIndication	(200.0)


#endif /* COMMUNICATION_DATAFORMAT_H_ */
