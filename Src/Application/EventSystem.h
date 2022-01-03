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
	Event_DataReadyToTransmit 	= 0x0001,
	Event_USBConnected		 	= 0x0002,
	Event_USBDisconnected		= 0x0004,
	Event_Other					= 0x0008,
	Event_DataReadyForAverage	= 0x0010
}Event_t;

void EventSystem_Initialize();
void EventSystem_HandleEvent();

void EventSystem_Signalize(Event_t eEvent);

#endif /* APPLICATION_EVENTSYSTEM_H_ */
