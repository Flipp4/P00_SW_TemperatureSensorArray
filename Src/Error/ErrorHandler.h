/*
 * ErrorHandler.h
 *
 *  Created on: 5 sty 2022
 *      Author: Filip
 */

#ifndef ERROR_ERRORHANDLER_H_
#define ERROR_ERRORHANDLER_H_

#include "ErrorList.h"

#define dErrorResetTicks

void ErrorHandler_Initalize();
void ErrorHandler_Tick();
void ErrorHandler_Handle();

void AssertError(AppErrorList_t eAppError);


#endif /* ERROR_ERRORHANDLER_H_ */
