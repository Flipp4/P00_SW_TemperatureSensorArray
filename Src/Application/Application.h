/*
 * Application.h
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "../Error/ErrorList.h"
#include "../Drivers/MCP9808/MCP9808_ArrayData.h"

void ApplicationPerform();
void AsynchronousTaskTimerUpdate();

void AssertError(AppErrorList_t eAppError);

#endif /* APPLICATION_APPLICATION_H_ */


