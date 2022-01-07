/*
 * EventSystem.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_EVENTSYSTEM_H_
#define APPLICATION_EVENTSYSTEM_H_

#define dEventCount  4

typedef enum Event_t
{
	eEvent_DataReadyToTransmit 	= 0x0001,
	eEvent_USBConnected		 	= 0x0002,
	eEvent_USBDisconnected		= 0x0004,
	eEvent_Other				= 0x0008,
	eEvent_DataReadyForAverage	= 0x0010,
	eEvent_ResetSensors			= 0x0020,
	eEvent_ErrorSupervisor		= 0x0040,
	eEvent_SignalizeSensorError = 0x0080
}Event_t;

void EventSystem_Initialize();
void EventSystem_HandleEvent();

void EventSystem_Signalize(Event_t eEvent);

#endif /* APPLICATION_EVENTSYSTEM_H_ */
