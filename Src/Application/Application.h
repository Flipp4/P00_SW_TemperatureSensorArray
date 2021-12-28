/*
 * Application.h
 *
 *  Created on: 28 lis 2021
 *      Author: Filip
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "../../Drivers/Sensors/TemperatureSensor_ArrayData.h"
#include "../Error/ErrorList.h"

void ApplicationPerform();
void AsynchronousTaskTimerUpdate();

void AssertError(AppErrorList_t eAppError);

#endif /* APPLICATION_APPLICATION_H_ */


